void Exit (int); 
void Start (void); 
int DaemonSeed (void); 
int CheckConfig (void); 
int OpenTCPSocket (void); 
int BindSocket (int, struct sockaddr_in, struct sockaddr_in, int); 
int ConfValue(char* tag, char* var, int index, char *result);
int ConfValueEnum(char* tag);