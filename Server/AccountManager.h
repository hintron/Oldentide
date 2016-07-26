#ifndef OLDENTIDE_ACCOUNTMANAGER_H
#define OLDENTIDE_ACCOUNTMANAGER_H

class AccountManager{
    public:
        AccountManager();
        ~AccountManager();
        static int create_new_account(char *, char *);
        static int authenticate_account(char *, char *);
    private:
        static const long long int ITERATIONS;
};

#endif // OLDENTIDE_ACCOUNTMANAGER_H
