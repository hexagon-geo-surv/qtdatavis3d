/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

#ifndef CUSTOMRENDERITEM_P_H
#define CUSTOMRENDERITEM_P_H

#include "abstractrenderitem_p.h"
#include "objecthelper_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class QCustom3DItem;

class CustomRenderItem : public AbstractRenderItem
{
public:
    CustomRenderItem();
    CustomRenderItem(const CustomRenderItem &other);
    virtual ~CustomRenderItem();

    inline void setTexture(GLuint texture) { m_texture = texture; }
    inline GLuint texture() const { return m_texture; }
    void setMesh(const QString &meshFile);
    inline ObjectHelper *mesh() const { return m_object; }
    inline void setScaling(const QVector3D &scaling) { m_scaling = scaling; }
    inline QVector3D scaling() const { return m_scaling; }
    inline void setBlendNeeded(bool blend) { m_needBlend = blend; }
    inline bool isBlendNeeded() const { return m_needBlend; }
    inline void setVisible(bool visible) { m_visible = visible; }
    inline bool isVisible() const { return m_visible; }
    inline void setItemPointer(QCustom3DItem *item) { m_item = item; }
    inline QCustom3DItem *itemPointer() const { return m_item; }
    inline void setValid(bool valid) { m_valid = valid; }
    inline bool isValid() const { return m_valid; }
    inline void setIndex(int index) { m_index = index; }
    inline int index() const { return m_index; }

private:
    GLuint m_texture;
    QVector3D m_scaling;
    ObjectHelper *m_object;
    bool m_needBlend;
    bool m_visible;
    bool m_valid;
    int m_index;
    QCustom3DItem *m_item;
 };
typedef QHash<QCustom3DItem *, CustomRenderItem *> CustomRenderItemArray;

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
