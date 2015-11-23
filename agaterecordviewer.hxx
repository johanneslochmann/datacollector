#pragma once

#include "htmlviewer.hxx"

#include "agaterecord.hxx"

class AgateRecordViewer : public HTMLViewer
{
    Q_OBJECT
public:
    explicit AgateRecordViewer(QWidget* p);

signals:

public slots:
    void setSurvey(int id);

protected:
    void showRecord(int id);
    QString format(AgateRecordSPtr r) const;
    QString formatHousekeepingData(AgateRecordSPtr r) const;
    QString formatTableRow(const QString& label, const QString& value) const;
    QString formatTableRow(const QString& label, const int value) const;
};

