#pragma once

class Action
{
    std::string m_type ="none";
    std::string m_name ="None";
    public:
        Action(){}
        Action(const std::string &name,const std::string &type);
        
        const std::string &name() const;
        const std::string &type()const;
        std::string &tostring() const;
}