#ifndef OLDENTIDE_ACCOUNTMANAGER_H
#define OLDENTIDE_ACCOUNTMANAGER_H

class AccountManager{
    public:
        AccountManager();
        ~AccountManager();
        static int create_new_account(char *, char *);
        static int authenticate_key(char *, char *);
        static int authenticate_account(char *, char *);
        static long long int generate_key(char *, char *, char **);
        static int check_password_length(char *);
        static int check_account_name_length(char *);
        static int sanitize_account_name(char *);
        static int sanitize_alphanumeric(char *);
        //static int sanitize_hex_string(char *);
        //static int sanitize_password(char *);
    private:
        static const long long int ITERATIONS;
};

#endif // OLDENTIDE_ACCOUNTMANAGER_H
