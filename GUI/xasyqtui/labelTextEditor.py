# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'windows/labelTextEditor.ui'
#
# Created by: PyQt5 UI code generator 5.15.10
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(473, 424)
        self.verticalLayout = QtWidgets.QVBoxLayout(Dialog)
        self.verticalLayout.setObjectName("verticalLayout")
        self.frame = QtWidgets.QFrame(Dialog)
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.frame)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setContentsMargins(-1, 0, -1, -1)
        self.gridLayout.setObjectName("gridLayout")
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem, 0, 2, 1, 1)
        self.chkMathMode = QtWidgets.QCheckBox(self.frame)
        self.chkMathMode.setObjectName("chkMathMode")
        self.gridLayout.addWidget(self.chkMathMode, 0, 0, 1, 1)
        self.cmbMathStyle = QtWidgets.QComboBox(self.frame)
        self.cmbMathStyle.setEnabled(False)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Maximum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.cmbMathStyle.sizePolicy().hasHeightForWidth())
        self.cmbMathStyle.setSizePolicy(sizePolicy)
        self.cmbMathStyle.setMinimumSize(QtCore.QSize(100, 0))
        self.cmbMathStyle.setObjectName("cmbMathStyle")
        self.cmbMathStyle.addItem("")
        self.cmbMathStyle.addItem("")
        self.cmbMathStyle.addItem("")
        self.gridLayout.addWidget(self.cmbMathStyle, 0, 1, 1, 1)
        self.verticalLayout_3.addLayout(self.gridLayout)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.txtLabelEdit = QtWidgets.QPlainTextEdit(self.frame)
        self.txtLabelEdit.setObjectName("txtLabelEdit")
        self.verticalLayout_2.addWidget(self.txtLabelEdit)
        self.verticalLayout_3.addLayout(self.verticalLayout_2)
        self.verticalLayout_4 = QtWidgets.QVBoxLayout()
        self.verticalLayout_4.setContentsMargins(-1, 0, -1, -1)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.label = QtWidgets.QLabel(self.frame)
        self.label.setObjectName("label")
        self.verticalLayout_4.addWidget(self.label)
        self.lblLabelPreview = QtWidgets.QLabel(self.frame)
        self.lblLabelPreview.setMinimumSize(QtCore.QSize(0, 100))
        self.lblLabelPreview.setFrameShape(QtWidgets.QFrame.Box)
        self.lblLabelPreview.setText("")
        self.lblLabelPreview.setObjectName("lblLabelPreview")
        self.verticalLayout_4.addWidget(self.lblLabelPreview)
        self.verticalLayout_3.addLayout(self.verticalLayout_4)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        spacerItem1 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem1)
        self.btnGetText = QtWidgets.QPushButton(self.frame)
        self.btnGetText.setMaximumSize(QtCore.QSize(32, 32))
        self.btnGetText.setText("")
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icons/text.svg"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.btnGetText.setIcon(icon)
        self.btnGetText.setFlat(True)
        self.btnGetText.setObjectName("btnGetText")
        self.horizontalLayout.addWidget(self.btnGetText)
        self.btnPreview = QtWidgets.QPushButton(self.frame)
        self.btnPreview.setMaximumSize(QtCore.QSize(32, 32))
        self.btnPreview.setText("")
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/icons/eye.svg"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.btnPreview.setIcon(icon1)
        self.btnPreview.setFlat(True)
        self.btnPreview.setObjectName("btnPreview")
        self.horizontalLayout.addWidget(self.btnPreview)
        self.btnCancel = QtWidgets.QPushButton(self.frame)
        self.btnCancel.setMaximumSize(QtCore.QSize(32, 32))
        self.btnCancel.setText("")
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/icons/android-close.svg"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.btnCancel.setIcon(icon2)
        self.btnCancel.setFlat(True)
        self.btnCancel.setObjectName("btnCancel")
        self.horizontalLayout.addWidget(self.btnCancel)
        self.btnAccept = QtWidgets.QPushButton(self.frame)
        self.btnAccept.setMaximumSize(QtCore.QSize(32, 32))
        self.btnAccept.setText("")
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/icons/android-done.svg"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.btnAccept.setIcon(icon3)
        self.btnAccept.setFlat(True)
        self.btnAccept.setObjectName("btnAccept")
        self.horizontalLayout.addWidget(self.btnAccept)
        self.verticalLayout_3.addLayout(self.horizontalLayout)
        self.verticalLayout.addWidget(self.frame)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
        self.chkMathMode.setText(_translate("Dialog", "Math Mode"))
        self.cmbMathStyle.setItemText(0, _translate("Dialog", "Inline Style"))
        self.cmbMathStyle.setItemText(1, _translate("Dialog", "Display Style"))
        self.cmbMathStyle.setItemText(2, _translate("Dialog", "Script Style"))
        self.label.setText(_translate("Dialog", "Preview"))
from xasyicons import icons_rc
