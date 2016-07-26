#ifndef OLDENTIDE_LOGINMANAGER_H
#define OLDENTIDE_LOGINMANAGER_H

class LoginManager{
    public:
        LoginManager();
        ~LoginManager();
        static int create_new_account(char *, char *);
        static int authenticate_account(char *, char *);
        static long long int generate_key(char *, char *, char **);
    private:
        static const long long int ITERATIONS;
};

#endif // OLDENTIDE_LOGINMANAGER_H
