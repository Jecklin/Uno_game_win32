#ifndef DATATYPEDEFINE_H
#define DATATYPEDEFINE_H
enum ECardAction
{
    ECA_Invalid     =   -1,
    ECA_None        =   0x00,
    ECA_AddTwo      =   0x01,
    ECA_AddFour     =   0x02,
    ECA_Reverse     =   0x04,
    ECA_Stop        =   0x08,
    ECA_ChangeColor =   0x10,
    ECA_ActionTwo   =   ECA_AddTwo  | ECA_Stop,
    ECA_Black       =   ECA_Stop    | ECA_ChangeColor,
    ECA_BlackFour   =   ECA_AddFour | ECA_Stop      | ECA_ChangeColor

};

enum ECardColor
{
    ECC_Invalid     =   -1,
    ECC_Red         =   0x1,
    ECC_Yellow      =   0x2,
    ECC_Blue        =   0x4,
    ECC_Green       =   0x8,
    ECC_Black       =   ECC_Red | ECC_Yellow | ECC_Blue | ECC_Green,

};

enum ECardId
{
    ECI_Invalid     =   -1,
    ECI_Zero        =   0 ,
    ECI_One               ,
    ECI_Two               ,
    ECI_Three             ,
    ECI_Four              ,
    ECI_Five              ,
    ECI_Six               ,
    ECI_Seven             ,
    ECI_Eight             ,
    ECI_Nine              ,
    ECI_AddTwo            ,
    ECI_Resverse          ,
    ECI_Stop              ,
    ECI_Black             ,
    ECI_BlackFour
};
#endif // DATATYPEDEFINE_H
