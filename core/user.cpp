#include "user.hpp"

User::User()
{

}

User::~User()
{

}

int User::getUserid() const
{
    return userid;
}

void User::setUserid(int value)
{
    userid = value;
}
QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &value)
{
    username = value;
}




