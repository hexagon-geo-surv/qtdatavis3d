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

import QtQuick 2.1
import QtDataVisualization 1.0

Item {
    property alias column: columnAxis
    property alias value: valueAxis
    property alias total: totalAxis

    // For row labels we can use row labels from data proxy, so default axis
    // suffices for rows.

    // Custom labels for columns, since the data contains abbreviated month names.
    //! [0]
    CategoryAxis3D {
        id: columnAxis
        labels: ["January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"]
    }
    //! [0]
    CategoryAxis3D {
        id: totalAxis
        labels: ["Yearly total"]
    }
    ValueAxis3D {
        id: valueAxis
        min: 0
        max: 35
        labelFormat: "%.2f M\u20AC"
        title: "Monthly income"
    }
}
