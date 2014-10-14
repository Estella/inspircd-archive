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


/* Counts the number of tags of a certain type within the config file, e.g. to enumerate opers */

int ConfValueEnum(char* tag)
{
	FILE *config;
	int ptr = 0;
	char buffer[MAXBUF], c_tag[MAXBUF], c;
	int in_token, in_quotes, tptr, j, idx = 0;
	char* key;

	if ((config = fopen (CONFIG_FILE, "r")) == NULL)
	{
		return 0;
	}
	else
	{
		ptr = 0;
		in_token = 0;
		in_quotes = 0;
		while (!feof(config))
		{
			c = fgetc(config);
			if ((c == '<') && (!in_quotes))
			{
				tptr = 0;
				in_token = 1;
				do {
					c = fgetc(config);
					if (c != ' ')
					{
						c_tag[tptr++] = c;
						c_tag[tptr] = '\0';
					}
				} while (c != ' ');
			}
			if (c == '"')
			{
				in_quotes = (!in_quotes);
			}
			if ((c == '>') && (!in_quotes))
			{
				in_token = 0;
				if (!strcmp(c_tag,tag))
				{
					/* correct tag, but wrong index */
					idx++;
				}
				c_tag[0] = '\0';
				buffer[0] = '\0';
				ptr = 0;
				tptr = 0;
			}
			if (c != '>')
			{
				if ((in_token) && (c != '\n') && (c != '\r'))
				{
					buffer[ptr++] = c;
					buffer[ptr] = '\0';
				}
			}
		}
	}
	fclose(config);
	return idx;
}





/* Retrieves a value from the config file. If there is more than one value of the specified
 * key and section (e.g. for opers etc) then the index value specifies which to retreive, e.g.
 *
 * ConfValue("oper","name",2,result);
 */

int ConfValue(char* tag, char* var, int index, char *result)
{
	FILE *config;
	int ptr = 0;
	char buffer[MAXBUF], c_tag[MAXBUF], c;
	int in_token, in_quotes, tptr, j, idx = 0;
	char* key;

	if ((config = fopen (CONFIG_FILE, "r")) == NULL)
	{
		return 0;
	}
	else
	{
		ptr = 0;
		in_token = 0;
		in_quotes = 0;
		while (!feof(config))
		{
			c = fgetc(config);
			if ((c == '<') && (!in_quotes))
			{
				tptr = 0;
				in_token = 1;
				do {
					c = fgetc(config);
					if (c != ' ')
					{
						c_tag[tptr++] = c;
						c_tag[tptr] = '\0';
					}
				} while (c != ' ');
			}
			if (c == '"')
			{
				in_quotes = (!in_quotes);
			}
			if ((c == '>') && (!in_quotes))
			{
				in_token = 0;
				if (idx == index)
				{
					if (!strcmp(c_tag,tag))
					{
						if ((buffer) && (c_tag) && (var))
						{
							key = strstr(buffer,var);
							if (!key)
							{
								/* value not found in tag */
								fclose(config);
								return 0;
							}
							else
							{
								key+=strlen(var);
								while (key[0] !='"')
								{
									if (!strlen(key))
									{
										/* missing quote */
										return 0;
									}
									key++;
								}
								key++;
								for (j = 0; j < strlen(key); j++)
								{
									if (key[j] == '"')
									{
										key[j] = '\0';
									}
								}
								fclose(config);
								strcpy(result,key);
								return 1;
							}
						}
					}
				}
				if (!strcmp(c_tag,tag))
				{
					/* correct tag, but wrong index */
					idx++;
				}
				c_tag[0] = '\0';
				buffer[0] = '\0';
				ptr = 0;
				tptr = 0;
			}
			if (c != '>')
			{
				if ((in_token) && (c != '\n') && (c != '\r'))
				{
					buffer[ptr++] = c;
					buffer[ptr] = '\0';
				}
			}
		}
	}
	fclose(config);
	return 0;
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

