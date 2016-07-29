#ifndef OLDENTIDE_LOGINMANAGER_H
#define OLDENTIDE_LOGINMANAGER_H

class LoginManager{
    public:
        LoginManager();
        ~LoginManager();
        static void generate_salt_and_key(char *, char *, char *);
        static long long int generate_key(char *, char *, char **);
    private:
        static const long long int ITERATIONS;
};

#endif // OLDENTIDE_LOGINMANAGER_H
