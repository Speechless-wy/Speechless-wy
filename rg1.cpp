#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

bool haveDecimal;
bool havelBrackets;
double maxValue = 100;
char Operator[4];
int OperatorIndex = 0;
int count = 0;
double GetRandomDouble() {
    return ((double)(arc4random() % 10000000))/10000000 * maxValue;
}

void InputOperator() {
    std::cout << "请输入所有需要的运算符：" << std::endl;
    std::string temp;
    std::cin >> temp;
    for(auto s:temp)
    {
        if(s == '+'||s == '-'||s == '*'||s == '/')
        {
            Operator[OperatorIndex++] = s;
        }
    }
}
void Init()
{
    srand(time(nullptr));
    std::cout << "请输入最大数值：" << std::endl;
    std::cin >> maxValue;
    InputOperator();
    std::cout << "请输入是否有小数：" << std::endl;
    std::cout << "是输入Yes，否则输入No" << std::endl;
    std::string temp;
    std::cin >> temp;
    if (temp == "Yes")
    {haveDecimal = true;}
    else
    {haveDecimal = false;}


    std::cout << "请输入是否有括号：" << std::endl;
    std::cout << "是输入Yes，否则输入No" << std::endl;
    std::cin >> temp;
    if (temp == "Yes")
    {havelBrackets = true;}
    else
    {havelBrackets = false;}

    std::cout << "题目的数量：" << std::endl;
    std::cin >> count;
}
char choose_a_Brackets()
{
    int index = (int)(rand()%OperatorIndex);
    if(index < 0){index = -index;}
    return Operator[(int)(index)];
}
std::string doubleToString(double a)
{
    std::stringstream ss;      //stringstream需要sstream头文件
    std::string str;
    ss<<a;
    ss>>str;
    return str;
}
std::string IntToString(int a)
{
    std::stringstream ss;      //stringstream需要sstream头文件
    std::string str;
    ss<<a;
    ss>>str;
    return str;
}
std::string Formula_a_b_c(){
    char op = choose_a_Brackets();
    double a = GetRandomDouble();
    double b = GetRandomDouble();
    char temp[128];
    char temp1[128];
    sprintf(temp,"%5.5lf",a);
    sprintf(temp1,"%5.5lf",b);
    if(haveDecimal)
    {
        return std::string(temp)+op+temp1;
    }
    else
    {
        return IntToString((int)a)+op+IntToString((int)b);
    }
}
std::string Formula_a_a_b_c(){
    char opLeft = choose_a_Brackets();
    char opRight = choose_a_Brackets();
    //a*(b*c)=
    double a = GetRandomDouble();
    double b = GetRandomDouble();
    double c = GetRandomDouble();
    char temp[128];
    char temp1[128];
    char temp2[128];
    sprintf(temp,"%5.5lf",a);
    sprintf(temp1,"%5.5lf",b);
    sprintf(temp2,"%5.5lf",c);
    if(haveDecimal)
    {
        return std::string(temp)+opLeft+'('+std::string(temp1)+opRight+std::string(temp2)+')';
    } else
    {
        return IntToString((int)a)+opLeft+'('+IntToString((int)b)+opRight+IntToString((int)c)+')';
    };
}

int main() {
    std::cout<<"------"<<GetRandomDouble() <<std::endl;
    Init();
    std::string result;

    std::ofstream file("output.txt");
    for(int i = 0;i<count;i++)
    {
        if(((int)GetRandomDouble())%2 == 0)
        {
            result += Formula_a_b_c() + '\n';
        }else
        {
            result += Formula_a_a_b_c() + '\n';
        }
    }
    std::cout.precision(4);
    file<<result<<std::endl;
    file.close();
    return 0;
}
