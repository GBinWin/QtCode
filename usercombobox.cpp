#include "usercombobox.h"

userComboBox::userComboBox(QWidget *parent):QComboBox(parent)
{

}

userComboBox::~userComboBox()
{

}

void userComboBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();  //触发clicked信号
    }

    QComboBox::mousePressEvent(event);  //将该事件传给父类处理，这句话很重要，如果没有，父类无法处理本来的点击事件
}
