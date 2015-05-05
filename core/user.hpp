#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    ~User();

    int getUserid() const;
    void setUserid(int value);

    QString getUsername() const;
    void setUsername(const QString &value);

private :
    QString username;
    int userid;
};

#endif // USER_H
