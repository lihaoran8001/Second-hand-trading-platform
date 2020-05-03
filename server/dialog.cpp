#include <QMessageBox>
#include<QTime>
#include "dialog.h"
#include "ui_dialog.h"
struct user_login
{
    QString ID;
    QString PassWord;
};
//登陆时所需要的账户信息
struct user_info
{
    QString ID;
    QString PassWord;
    QString phonenumber;
    QString cre;
};
//注册时需要的账户信息
//总控制初始化
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog), count(0),ordercount(1)
{
    ui->setupUi(this);

    ui->num->setText(QString("%1").arg(count));

    server = new Server(this);
    //监听本机网络
    server->listen(QHostAddress::Any, 8000);

    connect(ui->clearBtn, SIGNAL(clicked()), this, SLOT(clearMsg()));

}

Dialog::~Dialog()
{
    delete ui;
}
//有新的连接时的槽函数
void Dialog::showConnection()
{
    count++;


    /* change connect number while connection is connecting */
    ui->num->setText(QString("%1").arg(count));

}
//失去一个连接的槽函数
void Dialog::showDisconnection(int socketDescriptor)
{
    count--;

    /* remove disconnect socketdescriptor from list */
    server->socketList.removeAll(socketDescriptor);


    //change connect number while connection is disconnecting
    ui->num->setText(QString("%1").arg(count));
}



//总接受处理函数
void Dialog::revData(QString peerAddr, QByteArray data)
{
    QString msg;
    msg.prepend(data);
    ui->msg->append(peerAddr);
    ui->msg->append(msg);

    QString datae;
    datae.prepend(data);
    QString header=datae.section('/',1,1);
    if(datae=="new")
    {
        QString New="/new/"+QString::number(server->socketList.last());
        //ui->msg->append(New);
        emit sendData(New.toUtf8(),server->socketList.last());
    }
    if(header=="login")//登陆时的密令
    {
       Read_And_Check(datae.section('/',2,2),datae.section('/',3,3),datae.section('/',4,4));
       return;
    }
    if(header=="havelogged1")//用户已经登陆，恢复未完成订单
    {
        QString CId=datae.section('/',2,2);
        QString ID=datae.section('/',3,3);
        Renew_orders(CId,ID);
        return;
    }
    if(header=="havelogged2")
    {
        QString CId=datae.section('/',2,2);
        QString ID=datae.section('/',3,3);
        Renew_orders2(CId,ID);
        return;
    }
    if(header=="havelogged3")
    {
        QString CId=datae.section('/',2,2);
        //QString ID=datae.section('/',3,3);
        Renew_order3(CId);
        return;
    }
    if(header=="register")//注册时的密令
    {
      Store_User_Info(datae.section('/',2,2),datae.section('/',3,3),datae.section('/',4,4),datae.section('/',5,5));
      return;
    }
    if(header=="xiugaiziliao")//修改密码时的密令
    {
        QString CId=datae.section('/',2,2);
        QString ID=datae.section('/',3,3);
        QString oldpsd=datae.section('/',4,4);
        QString newpsd=datae.section('/',5,5);
        QString pnb=datae.section('/',6,6);
        Read_Check_Revise(CId,ID,oldpsd,newpsd,pnb);
        return;
    }
    if(header=="logout")//注销用户时的密令
   {
     Read_And_Delete(datae.section('/',2,2),datae.section('/',3,3),datae.section('/',4,4));
     return;
   }
    if(header=="orders")//用户发布订单的密令
    {
      //QString Cid=datae.section('/',2,2);
      QString id=datae.section('/',3,3);
      QString things=datae.section('/',4,4);
      QString from=datae.section('/',5,5);
      QString to=datae.section('/',6,6);
      QString time=datae.section('/',7,7);
      QString money=datae.section('/',8,8);
      Handle_the_orders(id,things,from,to,time,money);
      return;
    }
    if(header=="woyaojiedan")//用户要接单的密令
    {
      //  QString Cid=datae.section('/',2,2);
        QString num=datae.section('/',3,3);
        QString recid=datae.section('/',4,4);
        Received_orders(num,recid);
        return;
    }
    if(header=="woyaoquxiao")//用户取消订单的密令
    {
       // QString Cid=datae.section('/',2,2);
        QString num=datae.section('/',3,3);
        Cancel_orders(num);
    }
    if(header=="yiwancheng")//用户已完成订单
    {
      //  QString Cid=datae.section('/',2,2);
        QString num=datae.section('/',3,3);
        QString changecre=datae.section('/',4,4);
        Finish_orders(num,changecre);
    }
    if(header=="searchfor")
    {
        QString Cid=datae.section('/',2,2);
        QString from=datae.section('/',3,3);
        QString to=datae.section('/',4,4);
        searchfun(Cid,from,to);
        return;
    }
}

//向刚登陆的客户端发送已有订单信息
void Dialog::Renew_order3(QString cid)
{
    DataBase2* pdd=DataBase2::getDatabaseInstence();
    int ord=ordercount;
    int alreadysend=0;
    while(ord>1&&alreadysend<3)
    {
        QString *ptr=pdd->re(ord-1);
        if((pdd->whether(ord-1)==true)&&(ptr[7]==""))
        {
            QString numm=QString::number(ord-1);
            QString id=ptr[0];
            QString things=ptr[1];
            QString from=ptr[2];
            QString to=ptr[3];
            QString time=ptr[4];
            QString money=ptr[5];
            QString cre=ptr[6];
            QString return_data="/1/"+numm+"/"+id+"/"+things+"/"+from+"/"+to+"/"+time+"/"+money+"/"+cre;
            ui->msg->append(return_data);
            emit sendData(return_data.toUtf8(),cid.toInt());
            alreadysend++;
            QTime timer;

            timer.start();

            while(timer.elapsed() < 500)             //等待时间流逝0.5秒钟

            QCoreApplication::processEvents();
        }
        ord--;
    }
    ui->msg->append("logged3 end");
    return;
}
//响应搜索
void Dialog::searchfun(QString cid,QString from,QString to)
{
    DataBase2* pdd=DataBase2::getDatabaseInstence();
    int numofrec=pdd->Record(from,to);
    QString *record=pdd->pFind(from,to);
    for(int i=0;i<numofrec;i++)
    {
        QString num=record[9*i];
        if((record[9*i+8]=="")&&(pdd->whether(num.toInt())==true))
        {
        QString id1=record[9*i+1];
        QString things=record[9*i+2];
        QString from=record[9*i+3];
        QString to=record[9*i+4];
        QString time=record[9*i+5];
        QString money=record[9*i+6];
        QString cre=record[9*i+7];
        QString return_data="/result/"+num+"/"+id1+"/"+things+"/"+from+"/"+to+"/"+time+"/"+money+"/"+cre;
        ui->msg->append(return_data);
        emit sendData(return_data.toUtf8(),cid.toInt());

        QTime timer;

        timer.start();

        while(timer.elapsed() < 500)             //等待时间流逝0.5秒钟

        QCoreApplication::processEvents();
        }
    }
    ui->msg->append("noresult");
    emit sendData("/noresult/",cid.toInt());
    return;
}
//向刚登陆的客户端恢复他的订单信息2
void Dialog::Renew_orders2(QString cid,QString id)
{
    DataBase2* pdd=DataBase2::getDatabaseInstence();
    int numofrec=pdd->id2Record(id);
    QString *record=pdd->id2Find(id);
    for(int i=0;i<numofrec;i++)
    {
        QString num=record[9*i];
        QString id1=record[9*i+1];
        QString things=record[9*i+2];
        QString from=record[9*i+3];
        QString to=record[9*i+4];
        QString time=record[9*i+5];
        QString money=record[9*i+6];
        QString cre=record[9*i+7];
        QString return_data="/newbill/"+num+"/"+id1+"/"+things+"/"+from+"/"+to+"/"+time+"/"+money+"/"+cre;
        ui->msg->append(return_data);
        emit sendData(return_data.toUtf8(),cid.toInt());
        QTime timer;

        timer.start();

        while(timer.elapsed() < 500)             //等待时间流逝0.5秒钟

        QCoreApplication::processEvents();
    }
    ui->msg->append("nobill2");
    emit sendData("/nobill/",cid.toInt());
    return;
}
//向刚登陆的客户端恢复他的订单信息1
void Dialog::Renew_orders(QString cid,QString id)
{
    DataBase2* pdd=DataBase2::getDatabaseInstence();
    DataBase* pdb = DataBase::getDatabaseInstence();
    int numofpub=pdd->idRecord(id);
    QString *pubord=pdd->idFind(id);
    for(int i=0;i<numofpub;i++)
    {
        QString num=pubord[9*i];
        QString things=pubord[9*i+2];
        QString from=pubord[9*i+3];
        QString to=pubord[9*i+4];
        QString time=pubord[9*i+5];
        QString money=pubord[9*i+6];
        QString cre=pubord[9*i+7];
        QString id2=pubord[9*i+8];
        if(id2=="")
        {
           QString return_data="/newbill/"+num+"/"+id+"/"+things+"/"+from+"/"+to+"/"+time+"/"+money+"/"+cre+"/"+id2;
           ui->msg->append(return_data);
           emit sendData(return_data.toUtf8(),cid.toInt());
        }
        else
        {
        QString reccre=pdb->getCredit(id2);
        QString recpnb=pdb->getphone(id2);
        QString return_data="/newbill/"+num+"/"+id+"/"+things+"/"+from+"/"+to+"/"+time+"/"+money+"/"+cre+"/"+id2+"/"+reccre+"/"+recpnb;
        ui->msg->append(return_data);
        emit sendData(return_data.toUtf8(),cid.toInt());
        }
        QTime timer;

        timer.start();

        while(timer.elapsed() < 500)             //等待时间流逝0.5秒钟

        QCoreApplication::processEvents();
    }
    ui->msg->append("nobill1");
    emit sendData("/nobill/",cid.toInt());
    return;
}

//完成订单
void Dialog::Finish_orders(QString num,QString changecre)
{
    DataBase2* pdd=DataBase2::getDatabaseInstence();
    DataBase* pdb = DataBase::getDatabaseInstence();
    QString* ptr= pdd->re(num.toInt());
    QString id=ptr[0];
    QString id2=ptr[7];
    QString return_data="/3/"+num+"/"+id+"/"+id2;
    if((pdb->getCredit(id2)=="100")&&(changecre=="1"))
    {

    }
    else
    {
        int newcre=pdb->getCredit(id2).toInt()+changecre.toInt();
        QString newcrr=QString::number(newcre);
        pdb->revise_cre(id2,newcrr);
        ui->msg->append(id2+"credit revise success to"+newcrr);
    }
    if(pdd->deleteUsr(num.toInt())==1)
    {
      for(int i=0;i<server->socketList.length();i++)
      {
       emit sendData(return_data.toUtf8(),server->socketList[i]);
      }
    }
}
//取消订单
void Dialog::Cancel_orders(QString num)
{
     DataBase2* pdd=DataBase2::getDatabaseInstence();
     QString* ptr= pdd->re(num.toInt());
     QString id=ptr[0];
     QString id2=ptr[7];
     QString cre=ptr[6];
     QString return_data="/2/"+id+"/"+num+"/"+id2+"/"+cre+"/";
     if(pdd->deleteUsr(num.toInt())==1)
     {
       ui->msg->append("order"+num+"deleted");
       for(int i=0;i<server->socketList.length();i++)
       {
        ui->msg->append(return_data);
        emit sendData(return_data.toUtf8(),server->socketList[i]);
       }
     }
     return;
}
//接受订单
void Dialog::Received_orders(QString num,QString recid)
{
      DataBase2* pdd=DataBase2::getDatabaseInstence();
      DataBase* pdb = DataBase::getDatabaseInstence();
      QString recre=pdb->getCredit(recid);
      QString pnb=pdb->getphone(recid);
      QString* str=pdd->re(num.toInt());
      QString id=str[0];
      //
      QString return_data="/2/"+id+"/"+num+"/"+recid+"/"+recre+"/"+pnb;

      if(pdd->modifyUsr(num.toInt(),recid)==1)
      {
          for(int i=0;i<server->socketList.length();i++)
          {
             emit sendData(return_data.toUtf8(),server->socketList[i]);
          }
      }
      return;
}
//清空数据
void Dialog::clearMsg()
{
    ui->msg->clear();
}
//总发布订单
void Dialog::Handle_the_orders(QString id,QString things,QString from,QString to,QString time,QString money)
{
    DataBase2* pdd=DataBase2::getDatabaseInstence();
    DataBase* pdb = DataBase::getDatabaseInstence();
    QString cre=pdb->getCredit(id);
    QString id2="";
    if(pdd->insertUsr(ordercount,id,things,from,to,time,money,cre,id2)==1)
    {        
        QString num=QString::number(ordercount++,10);
        ui->msg->append("order"+num+"inserted");
        QString return_data="/1/"+num+"/"+id+"/"+things+"/"+from+"/"+to+"/"+time+"/"+money+"/"+cre;
        for(int i=0;i<server->socketList.length();i++)
        {
            ui->msg->append(return_data);
            emit sendData(return_data.toUtf8(),server->socketList[i]);
        }
    }
    return;
}
//用于插入注册时完整的用户信息
void Dialog::Store_User_Info(QString id,QString psd,QString pnb,QString cid)
{
         user_info userinfo;
         userinfo.ID=id;
         userinfo.PassWord=psd;
         userinfo.phonenumber=pnb;
         userinfo.cre="100";
         DataBase* pdb = DataBase::getDatabaseInstence();
         if(pdb->findUsr(userinfo.ID)==0)
         {
              if(pdb->insertUsr(userinfo.ID,userinfo.PassWord,userinfo.phonenumber,userinfo.cre)==true)
              {
                  ui->msg->append("zccg");
                  emit sendData("zhucechenggong", cid.toInt());
                  return;//表示注册插入成功
              }
              else
              {
                  ui->msg->append("zcsb1");
                  emit sendData("zhuceshibai", cid.toInt());
                  return;//服务器端插入失败
              }
         }
         else
         {
             ui->msg->append("zcsb2");
             emit sendData("zhanghaobeishiyong",cid.toInt());
              return ;//表示账号已被使用
         }
}
//用于检验登陆时密码和账户的一致性
void Dialog::Read_And_Check(QString id,QString psd,QString cid)
{
        user_login yh;
        yh.ID=id;
        yh.PassWord=psd;
        //进行检验data
        DataBase* pdb = DataBase::getDatabaseInstence();
        bool ret1 = pdb->findUsr(yh.ID);
        if(ret1)
        {
            bool ret2 = pdb->judge(yh.ID, yh.PassWord);
            if (ret2)
            {
                ui->msg->append("dlcg");
                QString r="/dlcg/"+yh.ID+"/"+pdb->getCredit(yh.ID)+"/"+pdb->getphone(yh.ID);
                ui->msg->append(cid);
                emit sendData(r.toUtf8(),cid.toInt());
                return;//返回正确值，可以登陆
            }
            else
            {
                ui->msg->append("mmcw");
                emit sendData("/mimacuowu/", cid.toInt());
                return;//密码错误
            }
        }
        else
        {
            ui->msg->append("zhcw");
            emit sendData("/zhanghaocuowu/",  cid.toInt());
            return ;//不存在这样的账号
        }
}

//用于修改密码
void Dialog::Read_Check_Revise(QString cid,QString id,QString oldpsd,QString newpsd,QString newpnb)
{
    user_login yh;
    yh.ID=id;
    yh.PassWord=oldpsd;
    //进行检验data
    DataBase* pdb = DataBase::getDatabaseInstence();
    bool ret1 = pdb->findUsr(yh.ID);
    if(ret1)
    {
       bool ret2 = pdb->judge(yh.ID, yh.PassWord);
       if (ret2)
       {
              ui->msg->append("进行修改...");
              pdb->revise(yh.ID,newpsd);
              pdb->revise_pnb(yh.ID,newpnb);
              emit sendData("xiugaichenggong", cid.toInt());
              return;//返回正确值，可以修改
       }
       else
       {
           ui->msg->append("密码错误...");
           emit sendData("mimacuowu", cid.toInt());
          return ;//密码错误
       }
    }
    else
    {
        ui->msg->append("账号错误...");
        emit sendData("zhanghaocuowu", cid.toInt());
      return;//不存在这样的账号
    }
}

//用于注销一个用户的信息
void Dialog::Read_And_Delete(QString id,QString psd,QString cid)
{
    user_login yh;
    yh.ID=id;
    yh.PassWord=psd;
    //进行检验data
    DataBase* pdb = DataBase::getDatabaseInstence();
    bool ret1 = pdb->findUsr(yh.ID);
    if(ret1)
    {
        bool ret2 = pdb->judge(yh.ID, yh.PassWord);
        if (ret2)
        {
         pdb->delete_one(yh.ID);
         emit sendData("1", cid.toInt());
         return;//返回正确值，可以删除
        }
        else
        {
          emit sendData("0", cid.toInt());
         return;//密码错误
        }
    }
    else
    {
        emit sendData("2", cid.toInt());
         return ;//不存在这样的账号
    }
}
//删除所有用户信息
void Dialog::on_pushButton_clicked()
{

    if(QMessageBox::warning(this,"确认", "是否要删除?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)

    {

        DataBase* pdb = DataBase::getDatabaseInstence();
       pdb->delete_all();

    }

    //执行No
}
//删除所有订单信息
void Dialog::on_pushButton_2_clicked()
{ if(QMessageBox::warning(this,"确认", "是否要删除?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)

    {
        DataBase2* pdd=DataBase2::getDatabaseInstence();
        pdd->delete_all();
        ordercount=1;
    }

}
