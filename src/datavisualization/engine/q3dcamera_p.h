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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Q3DCAMERA_P_H
#define Q3DCAMERA_P_H

#include "datavisualizationglobal_p.h"
#include "q3dcamera.h"

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

class Q3DCamera;

class Q3DCameraPrivate
{
public:
    Q3DCameraPrivate(Q3DCamera *q);
    ~Q3DCameraPrivate();

    void sync(Q3DCamera &other);

    void setRotations(const QPointF &rotation);

public:
    Q3DCamera *q_ptr;

    QVector3D m_target;
    QVector3D m_up;

    QMatrix4x4 m_viewMatrix;

    GLfloat m_xRotation;
    GLfloat m_yRotation;
    int m_zoomLevel;
    QDataVis::CameraPreset m_activePreset;
};

QT_DATAVISUALIZATION_END_NAMESPACE

#endif // Q3DCAMERA_P_H