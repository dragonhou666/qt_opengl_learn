/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "window.h" 

#include <QGridLayout> 
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel> 
#include <QTimer> 
#include <QSurfaceFormat>

#include "VABO.h"
#include "EBO.h"
#include "Texture.h"
#include "base_draw.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle(tr("OpenGL Widgets"));
    resize(800, 600);

    QSurfaceFormat  format;
    format.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(format);

    QWidget * central = new QWidget(this);
    this->setCentralWidget(central);

    QVBoxLayout * VLayout = new QVBoxLayout(central);
    VLayout->setAlignment(Qt::AlignTop);
    QLabel *openGLLabel = new QLabel(tr("OpenGL"));
    openGLLabel->setAlignment(Qt::AlignHCenter);
    openGLLabel->setFixedHeight(20);
    VLayout->addWidget(openGLLabel);

    QHBoxLayout * hlayout = new QHBoxLayout();

    m_list = new QListWidget(central);
    connect(m_list,&QListWidget::clicked,this,&Window::on_listWidget_clicked);
    QStringList list_name = {"三角形绘制","VABO","EBO", "纹理"};
    m_list->addItems(list_name);
    hlayout->addWidget(m_list);

    m_tab = new QTabWidget();
    hlayout->addWidget(m_tab);
    hlayout->setStretch(0,1);
    hlayout->setStretch(1,7);

    VLayout->addLayout(hlayout);
    VLayout->setStretch(0,1);
    VLayout->addSpacing(5);
    VLayout->setStretch(1,9);
    central->setLayout(VLayout);
}

Window::~Window()
{

}

void Window::on_listWidget_clicked()
{
    m_tab->clear();
    MapImpl * map = nullptr;
    int index = m_list->currentRow();
    switch (index) {
        case 0:
        {
            map  = new BaseDraw(m_tab);
            break;
        }
        case 1:
        {
            map  = new VABO(m_tab);
            break;
        }
    case 2:
    {
        map  = new EBO(m_tab);
        break;
    }
    case 3:
    {
        map  = new Texture(m_tab);
        break;
    }
    default:
        return;
    }

    if (map)
    {
        m_tab->addTab(map,"测试");
    }

}
