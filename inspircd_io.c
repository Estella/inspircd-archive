#include "inspircd.h"
#include "inspircd_io.h"
#include "inspircd_util.h"


void Exit (int status)
{
  send_error("Server shutdown.");
  exit (status);
}

void Killed(int status)
{
  send_error("Server terminated.");
  exit(status);
}

void Rehash(int status)
{
  send_error("Rehashing...");
}



void Start (void)
{
  printf("Inspire Internet Relay Chat Server, compiled " __DATE__ " at " __TIME__ "\n");
  printf("(C) ChatSpike Development team.\n\n");
  printf("Developers: C.Edwards (Brain), C.McLure (FrostyCoolSlug)\n");
  printf("Documentation: FrostyCoolSlug\n");
  printf("Testers: piggles, Lord_Zathras, typobox43\n");
  printf("Name concept: Lord_Zathras\n\n");
}


int DaemonSeed (void)
{
  int childpid;
  signal (SIGALRM, SIG_IGN);
  signal (SIGHUP, Rehash);
  signal (SIGPIPE, SIG_IGN);
  signal (SIGTERM, Exit);
  signal (SIGABRT, Exit);
  signal (SIGSEGV, Error);
  signal (SIGURG, Exit);
  signal (SIGKILL, Exit);
  if ((childpid = fork ()) < 0)
    return (ERROR);
  else if (childpid > 0)
    exit (0);
  setsid ();
  chdir ("/");
  umask (077);
  /* close stdout, stdin, stderr */
  close(0);
  close(1);
  close(2);
  return (TRUE);
}




/* Make sure the config file is available */
int CheckConfig (void)
{
  FILE *input;

  if ((input = fopen (CONFIG_FILE, "r")) == NULL)
    {
      printf("ERROR: Cannot open config file: %s. Exiting\n");
      return(FALSE);
    }
  else
    fclose (input);

return(TRUE);
}



int ConfigTokenRetrieve (char *token, char *configToken)
{
  FILE *config;
  char buffer[MAXBUF], tokenBuffer[MAXBUF];
  int count = 0;

  if ((config = fopen (CONFIG_FILE, "r")) == NULL)
    {
      printf("ERROR: Cannot open config file: %s.\n", CONFIG_FILE);
      return (ERROR);
    }
  else
    {
      while ((fgets (buffer, MAXBUF, config)) != NULL)
	{
	  /* this skips comments */
	  if (buffer[0] != '#')
	    {
	      /* search for the token and make sure the trailing character */
	      /* is a " " or "=" to make sure the entire token was found */
	      if ((strstr (buffer, token) != (char) NULL) && 
		   ((buffer[strlen(token)] == '=') || (buffer[strlen(token)] == ' '))) 
		{		/* cut off the '=' and send it back */
		  if (strstr (buffer, "\"") == (char) NULL)
		    {
		      printf("Quotes missing from %s token. Option skipped\n", token);
		      fclose (config);
		      return (FALSE);
		    }

		  SafeStrncpy (tokenBuffer, strstr (buffer, "\"") + 1, MAXBUF);

		  /* strip off unprintables/linefeeds (if any) */
		  count = 0;
		  while (count < MAXBUF - 1)
		    {
		      if ((isprint (tokenBuffer[count])) && tokenBuffer[count] != '"')
			configToken[count] = tokenBuffer[count];
		      else
			{
			  configToken[count] = '\0';
			  break;
			}
		      count++;
		    }

		  configToken[MAXBUF - 1] = '\0';
		  fclose (config);
		  return (TRUE);
		}
	    }
	}
      fclose (config);
      return (FALSE);
    }

}


/* This will bind a socket to a port. It works for UDP/TCP */
int BindSocket (int sockfd, struct sockaddr_in client, struct sockaddr_in server, int port)
{
  bzero ((char *) &server, sizeof (server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl (INADDR_ANY);
  server.sin_port = htons (port);

  if (bind (sockfd, (struct sockaddr *) &server, sizeof (server)) < 0)
  {
    return (ERROR);
  }
  else
  {
    listen (sockfd, 5);
    return (TRUE);
  }
}


/* Open a TCP Socket */
int OpenTCPSocket (void)
{
  int sockfd;
  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    return (ERROR);
  else
    return (sockfd);
}


/* This function checks a config variable for a numerical flag and returns it */
int CheckFlag (char *flagName)
{
  char configToken[MAXBUF];

  if ((ConfigTokenRetrieve (flagName, configToken)) == TRUE)
  {
    return (atoi(configToken));
  }
  else
  {
    return (FALSE);
  }
}

