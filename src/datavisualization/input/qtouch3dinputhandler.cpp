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

#include "qtouch3dinputhandler_p.h"
#include "q3dcamera_p.h"
#include <QTimer>
#include <qmath.h>

QT_DATAVISUALIZATION_BEGIN_NAMESPACE

const qreal maxTapAndHoldJitter = 20;
const int maxPinchJitter = 10;
const int maxSelectionJitter = 5;
const int tapAndHoldTime = 250;
const float rotationSpeed = 200.0f;
const int minZoomLevel = 10;
const int maxZoomLevel = 500;

/*!
   \class QTouch3DInputHandler
   \inmodule QtDataVisualization
   \brief Basic touch display based input handler.
   \since 1.0.0

    QTouch3DInputHandler is the basic input handler for touch screen devices.
*/

/*!
 * Constructs the basic touch display input handler. An optional \a parent parameter can be given
 * and is then passed to QObject constructor.
 */
QTouch3DInputHandler::QTouch3DInputHandler(QObject *parent)
    : Q3DInputHandler(parent),
      d_ptr(new QTouch3DInputHandlerPrivate(this))
{
}

/*!
 *  Destroys the input handler.
 */
QTouch3DInputHandler::~QTouch3DInputHandler()
{
}

/*!
 * Override this to change handling of touch events.
 * Touch event is given in the \a event.
 */
void QTouch3DInputHandler::touchEvent(QTouchEvent *event)
{
    QList<QTouchEvent::TouchPoint> points;
    points = event->touchPoints();

    if (!scene()->isSlicingActive() && points.count() == 2) {
        d_ptr->m_holdTimer->stop();
        QPointF distance = points.at(0).pos() - points.at(1).pos();
        d_ptr->handlePinchZoom(distance.manhattanLength());
    } else if (points.count() == 1) {
        QPointF pointerPos = points.at(0).pos();
        if (event->type() == QEvent::TouchBegin) {
            if (scene()->isSlicingActive()) {
                if (scene()->isPointInPrimarySubView(pointerPos.toPoint()))
                    setInputState(QDataVis::InputOnOverview);
                else if (scene()->isPointInSecondarySubView(pointerPos.toPoint()))
                    setInputState(QDataVis::InputOnSlice);
                else
                    setInputState(QDataVis::InputNone);
            } else {
                // Handle possible tap-and-hold selection
                d_ptr->m_startHoldPos = pointerPos;
                d_ptr->m_touchHoldPos = d_ptr->m_startHoldPos;
                d_ptr->m_holdTimer->start();
                // Start rotating
                setInputState(QDataVis::InputRotating);
                setInputPosition(pointerPos.toPoint());
            }
        } else if (event->type() == QEvent::TouchEnd) {
            d_ptr->m_holdTimer->stop();
            // Handle possible selection
            d_ptr->handleSelection(pointerPos);
        } else if (event->type() == QEvent::TouchUpdate) {
            if (!scene()->isSlicingActive()) {
                d_ptr->m_touchHoldPos = pointerPos;
                // Handle rotation
                d_ptr->handleRotation(pointerPos);
            }
        }
    } else {
        d_ptr->m_holdTimer->stop();
    }
}

QTouch3DInputHandlerPrivate::QTouch3DInputHandlerPrivate(QTouch3DInputHandler *q)
    : q_ptr(q),
      m_holdTimer(0)
{
    m_holdTimer = new QTimer();
    m_holdTimer->setSingleShot(true);
    m_holdTimer->setInterval(tapAndHoldTime);
    connect(m_holdTimer, &QTimer::timeout, this, &QTouch3DInputHandlerPrivate::handleTapAndHold);
}

QTouch3DInputHandlerPrivate::~QTouch3DInputHandlerPrivate()
{
    m_holdTimer->stop();
    delete m_holdTimer;
}

void QTouch3DInputHandlerPrivate::handlePinchZoom(qreal distance)
{
    int newDistance = distance;
    int prevDist = q_ptr->prevDistance();
    if (prevDist > 0 && qAbs(prevDist - newDistance) < maxPinchJitter)
        return;
    q_ptr->setInputState(QDataVis::InputOnPinch);
    Q3DCamera *camera = q_ptr->scene()->activeCamera();
    int zoomLevel = camera->zoomLevel();
    qreal zoomRate = qSqrt(qSqrt(zoomLevel));
    if (newDistance > prevDist)
        zoomLevel += zoomRate;
    else
        zoomLevel -= zoomRate;
    if (zoomLevel > maxZoomLevel)
        zoomLevel = maxZoomLevel;
    else if (zoomLevel < minZoomLevel)
        zoomLevel = minZoomLevel;
    camera->setZoomLevel(zoomLevel);
    q_ptr->setPrevDistance(newDistance);
}

void QTouch3DInputHandlerPrivate::handleTapAndHold()
{
    QPointF distance = m_startHoldPos - m_touchHoldPos;
    if (distance.manhattanLength() < maxTapAndHoldJitter) {
        q_ptr->setInputPosition(m_touchHoldPos.toPoint());
        q_ptr->setInputState(QDataVis::InputOnScene);
    }
}

void QTouch3DInputHandlerPrivate::handleSelection(const QPointF &position)
{
    QPointF distance = m_startHoldPos - position;
    if (distance.manhattanLength() < maxSelectionJitter)
        q_ptr->setInputState(QDataVis::InputOnScene);
    else
        q_ptr->setInputState(QDataVis::InputNone);
    q_ptr->setPreviousInputPos(position.toPoint());
}

void QTouch3DInputHandlerPrivate::handleRotation(const QPointF &position)
{
    if (QDataVis::InputRotating == q_ptr->inputState()) {
        Q3DScene *scene = q_ptr->scene();
        Q3DCamera *camera = scene->activeCamera();
        QPointF rotations = camera->rotations();
        float xRotation = rotations.x();
        float yRotation = rotations.y();
        QPointF inputPos = q_ptr->inputPosition();
        float mouseMoveX = float(inputPos.x() - position.x())
                / (scene->viewport().width() / rotationSpeed);
        float mouseMoveY = float(inputPos.y() - position.y())
                / (scene->viewport().height() / rotationSpeed);
        xRotation -= mouseMoveX;
        yRotation -= mouseMoveY;
        camera->setRotations(QPointF(xRotation, yRotation));
        camera->d_ptr->updateViewMatrix(1.0f);

        q_ptr->setPreviousInputPos(inputPos.toPoint());
        q_ptr->setInputPosition(position.toPoint());
    }
}

QT_DATAVISUALIZATION_END_NAMESPACE
