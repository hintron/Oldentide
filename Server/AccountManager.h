#ifndef OLDENTIDE_ACCOUNTMANAGER_H
#define OLDENTIDE_ACCOUNTMANAGER_H

class AccountManager{
    public:
        AccountManager();
        ~AccountManager();
        //static int create_new_account(char *, char *, char *);
        static int authenticate_account(char *, char *);
};

#endif // OLDENTIDE_ACCOUNTMANAGER_H
