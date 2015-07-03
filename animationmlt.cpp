#include "animationmlt.h"

animationMLT::animationMLT()
{
    Properties pr;
    pr.set("foo", "50=100; 60|=60; 100~=0; 120=20");
    pr.anim_get_int("foo", 0);

    Animation an = pr.get_animation("foo");

    qDebug() << "Original Animation String" << an.serialize_cut(-1, -1);

    printOutput(pr, an);

    addKF(pr);

    printOutput(pr, an);
}

void animationMLT::addKF(Properties p)
{
    // Adds new keyframe
    p.anim_set("foo", 10, 88, 0, mlt_keyframe_discrete);
    qDebug() << "Discrete KF added";

    p.anim_set("foo", 5, 99, 0, mlt_keyframe_smooth);
    qDebug() << "Smooth KF added";
}

QString animationMLT::getKFType(Animation a, int index)
{
    // Returns KF type
    QString KFtype;

    if (a.key_get_type(index) == mlt_keyframe_smooth)
        KFtype = "~ smooth";
    if (a.key_get_type(index) == mlt_keyframe_linear)
        KFtype = "= linear";
    if (a.key_get_type(index) == mlt_keyframe_discrete)
        KFtype = "| discrete";

    return KFtype;
}

void animationMLT::printOutput(Properties p, Animation a)
{
    // Prints Info
    qDebug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    qDebug() << "Total Length of Animation:" << a.length();
    qDebug() << "No. of KFs:" <<a.key_count();

    int pos = 0;

    while (pos!=a.key_count()) {
        qDebug() << "frame:"<< a.key_get_frame(pos) << "value:" << p.anim_get_int("foo", a.key_get_frame(pos));
        qDebug() << "index:" << pos << "type:" << getKFType(a, pos);

        pos++;
    }

    qDebug() << "New Animation String" << a.serialize_cut(-1, -1);
    qDebug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}
