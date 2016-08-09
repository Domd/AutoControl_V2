/****************************************************************************
** Meta object code from reading C++ file 'testbasicfun.h'
**
** Created: Sat Jun 29 09:17:52 2013
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testbasicfun.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testbasicfun.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestBasicFun[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      38,   13,   13,   13, 0x08,
      58,   13,   13,   13, 0x08,
      78,   13,   13,   13, 0x08,
      98,   13,   13,   13, 0x08,
     118,   13,   13,   13, 0x08,
     138,   13,   13,   13, 0x08,
     158,   13,   13,   13, 0x08,
     178,   13,   13,   13, 0x08,
     198,   13,   13,   13, 0x08,
     224,   13,   13,   13, 0x08,
     237,   13,   13,   13, 0x08,
     263,   13,   13,   13, 0x08,
     283,   13,   13,   13, 0x08,
     303,   13,   13,   13, 0x08,
     327,   13,   13,   13, 0x08,
     351,   13,   13,   13, 0x08,
     375,   13,   13,   13, 0x08,
     399,   13,   13,   13, 0x08,
     419,   13,   13,   13, 0x08,
     439,   13,   13,   13, 0x08,
     459,   13,   13,   13, 0x08,
     482,   13,   13,   13, 0x08,
     511,  503,   13,   13, 0x08,
     535,  503,   13,   13, 0x08,
     559,  503,   13,   13, 0x08,
     583,  503,   13,   13, 0x08,
     607,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TestBasicFun[] = {
    "TestBasicFun\0\0on_toolButton_clicked()\0"
    "on_LEDtB1_clicked()\0on_LEDtB2_clicked()\0"
    "on_LEDtB3_clicked()\0on_LEDtB4_clicked()\0"
    "on_LEDtB5_clicked()\0on_LEDtB6_clicked()\0"
    "on_LEDtB7_clicked()\0on_LEDtB8_clicked()\0"
    "on_toolButton_2_clicked()\0buttonTest()\0"
    "on_toolButton_3_clicked()\0on_TbBack_clicked()\0"
    "on_Tb_ADC_clicked()\0on_Tb_Device0_clicked()\0"
    "on_Tb_Device1_clicked()\0on_Tb_Device2_clicked()\0"
    "on_Tb_Device3_clicked()\0on_Tb_PWM_clicked()\0"
    "on_Tb_SBF_clicked()\0on_Tb_Add_clicked()\0"
    "on_Tb_Reduce_clicked()\0on_Tb_Stop_clicked()\0"
    "checked\0on_Cb_LED_clicked(bool)\0"
    "on_Cb_KEY_clicked(bool)\0on_Cb_ADC_clicked(bool)\0"
    "on_Cb_PWM_clicked(bool)\0adcTest()\0"
};

const QMetaObject TestBasicFun::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TestBasicFun,
      qt_meta_data_TestBasicFun, 0 }
};

const QMetaObject *TestBasicFun::metaObject() const
{
    return &staticMetaObject;
}

void *TestBasicFun::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestBasicFun))
        return static_cast<void*>(const_cast< TestBasicFun*>(this));
    return QWidget::qt_metacast(_clname);
}

int TestBasicFun::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 1: on_LEDtB1_clicked(); break;
        case 2: on_LEDtB2_clicked(); break;
        case 3: on_LEDtB3_clicked(); break;
        case 4: on_LEDtB4_clicked(); break;
        case 5: on_LEDtB5_clicked(); break;
        case 6: on_LEDtB6_clicked(); break;
        case 7: on_LEDtB7_clicked(); break;
        case 8: on_LEDtB8_clicked(); break;
        case 10: buttonTest(); break;
        case 11: on_toolButton_3_clicked(); break;
        case 12: on_TbBack_clicked(); break;
        case 14: on_Tb_Device0_clicked(); break;
        case 15: on_Tb_Device1_clicked(); break;
        case 16: on_Tb_Device2_clicked(); break;
        case 17: on_Tb_Device3_clicked(); break;
        case 19: on_Tb_SBF_clicked(); break;
        case 20: on_Tb_Add_clicked(); break;
        case 21: on_Tb_Reduce_clicked(); break;
        case 22: on_Tb_Stop_clicked(); break;
        case 23: on_Cb_LED_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: on_Cb_KEY_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: on_Cb_ADC_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: on_Cb_PWM_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: adcTest(); break;
        default: ;
        }
        _id -= 28;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
