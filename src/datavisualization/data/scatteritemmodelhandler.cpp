/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVisualization module.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "scatteritemmodelhandler_p.h"
#include <QTimer>

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

ScatterItemModelHandler::ScatterItemModelHandler(QItemModelScatterDataProxy *proxy, QObject *parent)
    : AbstractItemModelHandler(parent),
      m_proxy(proxy)
{
}

ScatterItemModelHandler::~ScatterItemModelHandler()
{
}

// Resolve entire item model into QScatterDataArray.
void ScatterItemModelHandler::resolveModel()
{
    QItemModelScatterDataMapping *mapping = static_cast<QItemModelScatterDataMapping *>(m_activeMapping);
    if (m_itemModel.isNull() || !mapping) {
        m_proxy->resetArray(0);
        return;
    }

    static const int noRoleIndex = -1;

    QHash<int, QByteArray> roleHash = m_itemModel->roleNames();
    //const int labelRole = roleHash.key(mapping->labelRole().toLatin1(), noRoleIndex);
    const int xPosRole = roleHash.key(mapping->xPosRole().toLatin1(), noRoleIndex);
    const int yPosRole = roleHash.key(mapping->yPosRole().toLatin1(), noRoleIndex);
    const int zPosRole = roleHash.key(mapping->zPosRole().toLatin1(), noRoleIndex);
    // Default valueRole to display role if no mapping
    //const int valueRole = roleHash.key(mapping->valueRole().toLatin1(), Qt::DisplayRole);
    const int columnCount = m_itemModel->columnCount();
    const int rowCount = m_itemModel->rowCount();
    const int totalCount = rowCount * columnCount;
    int runningCount = 0;

    // Parse data into newProxyArray
    QScatterDataArray *newProxyArray = new QScatterDataArray(totalCount);
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            QModelIndex index = m_itemModel->index(i, j);
            //if (labelRole != noRoleIndex)
            //    (*newProxyArray)[runningCount].setLabel(index.data(labelRole).toString());
            float xPos(0.0f);
            float yPos(0.0f);
            float zPos(0.0f);
            if (xPosRole != noRoleIndex)
                xPos = index.data(xPosRole).toFloat();
            if (yPosRole != noRoleIndex)
                yPos = index.data(yPosRole).toFloat();
            if (zPosRole != noRoleIndex)
                zPos = index.data(zPosRole).toFloat();
            (*newProxyArray)[runningCount].setPosition(QVector3D(xPos, yPos, zPos));
            //(*newProxyArray)[runningCount].setValue(index.data(valueRole).toReal());
            runningCount++;
        }
    }

    m_proxy->resetArray(newProxyArray);
}

QT_DATAVISUALIZATION_END_NAMESPACE