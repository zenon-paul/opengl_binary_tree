#include"position.h"

XYi add_xyi(XYi a,XYi b){
    XYi res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}