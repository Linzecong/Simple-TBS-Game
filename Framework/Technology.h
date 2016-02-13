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
            case 100:
                Cost=0;
                Name="工业学";
                Des="可训练步兵";
                break;
            case 101:
                Cost=50;
                Name="动力学";
                Des="可训练火箭兵";
                break;
            case 102:
                Cost=100;
                Name="稀土开发";
                Des="产能+5每基地";
                break;
            case 103:
                Cost=150;
                Name="熔炼学";
                Des="产能+5每基地";
                break;
            case 104:
                Cost=200;
                Name="组装学";
                Des="可训机甲战士";
                break;
            case 105:
                Cost=300;
                Name="量子学";
                Des="可训练全能战士";
                break;
            case 106:
                Cost=300;
                Name="光子学";
                Des="治愈在场所有兵";
                break;
            case 107:
                Cost=500;
                Name="光子引擎";
                Des="产能+20每基地 可训练光速战机";
                break;
            case 108:
                Cost=500;
                Name="量子通信";
                Des="产能+20每基地 可训练量子战机";
                break;
            case 109:
                Cost=500;
                Name="星际规则";
                Des="产能+50每基地";
                break;
            case 110:
                Cost=1000;
                Name="升维";
                Des="在场所有兵防御+1 可训练瓦解炮";
                break;


            case 200:
                Cost=0;
                Name="献祭";
                Des="可训练沉沦魔";
                break;
            case 201:
                Cost=20;
                Name="剧毒传送门";
                Des="可训练剧毒蜘蛛";
                break;
            case 202:
                Cost=80;
                Name="压迫";
                Des="在场沉沦魔防御-1，攻击+1";
                break;
            case 203:
                Cost=110;
                Name="血池";
                Des="产能+10每基地";
                break;
            case 204:
                Cost=200;
                Name="法术";
                Des="可训练邪恶法师";
                break;
            case 205:
                Cost=250;
                Name="飞翼";
                Des="可训练邪恶毒蜂";
                break;
            case 206:
                Cost=300;
                Name="聚能术";
                Des="在场法师攻击距离+1";
                break;
            case 207:
                Cost=500;
                Name="死亡契约";
                Des="产能+20每基地 可训练镰刀魔";
                break;
            case 208:
                Cost=500;
                Name="大召唤术";
                Des="产能+20每基地 可训练剧毒蜂王";
                break;
            case 209:
                Cost=500;
                Name="高维召唤";
                Des="产能+40每基地";
                break;
            case 210:
                Cost=800;
                Name="亵渎";
                Des="可训练堕天使 治愈在场所有兵";
                break;

            case 300:
                Cost=0;
                Name="神迹";
                Des="可训练天使";
                break;
            case 301:
                Cost=50;
                Name="进化";
                Des="可训练大天使";
                break;
            case 302:
                Cost=100;
                Name="下凡";
                Des="在场兵攻击力+1 ";
                break;
            case 303:
                Cost=100;
                Name="聚能术";
                Des="产能+10每基地";
                break;
            case 304:
                Cost=200;
                Name="勇气";
                Des="可训练能天使";
                break;
            case 305:
                Cost=300;
                Name="力量";
                Des="可训练力天使";
                break;
            case 306:
                Cost=300;
                Name="圣洁";
                Des="治愈在场所有兵";
                break;
            case 307:
                Cost=500;
                Name="进阶";
                Des="产能+20每基地 可训练高阶天使";
                break;
            case 308:
                Cost=500;
                Name="升华";
                Des="产能+30每基地 可训练六翼天使";
                break;
            case 309:
                Cost=1000;
                Name="回到原点";
                Des="治愈在场所有兵 产能+40每基地";
                break;
            case 310:
                Cost=1200;
                Name="原点";
                Des="可训练创世神 产能+80每基地";
                break;
            }
}

#endif // TECHNOLOGY
