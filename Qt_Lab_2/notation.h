#ifndef NOTATION_H
#define NOTATION_H
#include <QString>

class Notation
{
private:
    QString _data;
    QString _time;
    QString _name;
    QString _text;

    QString _type;
    bool _availability = 1;

public:
    Notation();
    explicit Notation(const QString &data,
                        const QString &time,
                        const QString &name,
                        const QString &text,
                        const QString &type,
                        bool availability):
            _data(data), _time(time), _name(name), _text(text), _type(type), _availability(availability) {}
       QString data() const;
       void setData(const QString &data);
       QString time() const;
       void setTime(const QString &time);
       QString name() const;
       void setName(const QString &name);
       QString text() const;
       void setText(const QString &text);
       QString type() const;
       void setType(const QString &type);
       bool availability() const;
       void setAvailability(bool availability);
};

#endif // NOTATION_H
