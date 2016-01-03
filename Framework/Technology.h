/*科技*/
/*此头文件定义科技信息*/

#ifndef TECHNOLOGY_H
#define TECHNOLOGY_H
#include<QString>

class Technology{
public:
    int ID;//科技ID
    int Cost;//花费资金
    QString Name;
    QString Des;

public:
    Technology(int id);
};

Technology::Technology(int id){
            ID=id;

            /*************此处定义科技内容*************/
            switch(ID){
            case 0:
                Cost=0;
                Name="机枪兵科技";
                Des="解锁建造机枪兵";
                break;
            case 1:
                Cost=50;
                Name="防空兵科技";
                Des="解锁建造防空兵";
                break;
            case 2:
                Cost=200;
                Name="工业时代";
                Des="解锁建造坦克和轰炸机";
                break;
            case 3:
                Cost=200;
                Name="音速科技";
                Des="解锁建造歼击机";
                break;
            case 4:
                Cost=100;
                Name="产能加速";
                Des="产能+10";
                break;
            }
}

#endif // TECHNOLOGY
