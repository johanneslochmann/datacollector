#include "agaterecordviewer.hxx"

#include "agaterecordgateway.hxx"

#include "datacollector.hxx"

AgateRecordViewer::AgateRecordViewer(QWidget *p)
    : HTMLViewer(p)
{
}

void AgateRecordViewer::setSurvey(int id)
{
    clear();

    if (id < 1) {
        return;
    }

    showRecord(id);
}

void AgateRecordViewer::showRecord(int id)
{
    try {
        auto rec = AgateRecordGateway().loadById(id);

        setText(format(rec));
    }
    catch(DatabaseError e) {
        DataCollector::get()->showDatabaseError(e, tr("Failed to load survey with ID %1").arg(id), this);
    }
}

QString AgateRecordViewer::format(AgateRecordSPtr r) const
{
    QStringList buf;

    buf.append("<html>");
    buf.append("<head></head>");
    buf.append("<body>");
    buf.append(formatHousekeepingData(r));
    buf.append("</body>");
    buf.append("</html>");

    return buf.join("\n");
}

QString AgateRecordViewer::formatHousekeepingData(AgateRecordSPtr r) const
{
    QStringList buf;

    buf.append(QString("<p>%1</p>").arg("Housekepping Data"));
    buf.append("<table border=\"1\">");
    buf.append(formatTableRow(tr("Survey ID"), r->survey()->id()));
    buf.append(formatTableRow(tr("Survey Date"), r->survey()->date().toString(Qt::DefaultLocaleShortDate )));
    buf.append(formatTableRow(tr("Project"), r->project()->name()));
    buf.append(formatTableRow(tr("Campaign"), r->campaign()->name()));
    buf.append(formatTableRow(tr("Organization"), r->organization()->name()));
    buf.append("</table>");

    buf.append(QString("<p>%1</p>").arg("Proband"));
    buf.append("<table border=\"1\">");
    buf.append(formatTableRow(tr("Year Of Birth"), r->proband()->yearOfBirth()));
    buf.append(formatTableRow(tr("Sex"), r->sex()->name()));
    buf.append("</table>");

    buf.append(QString("<p>%1 (%2)</p>").arg("Diagnosis").arg(r->diagnosis().size()));
    buf.append("<table border=\"1\">");
    for (auto d : r->diagnosis()) {
        buf.append(formatTableRow(tr("ICD10"), d->name));
    }
    buf.append("</table>");

    buf.append(QString("<p>%1 (%2)</p>").arg("Depot").arg(r->depots().size()));
    buf.append("<table border=\"1\">");
    buf.append(QString("<tr><th>%1</th><th>%2</th><th>%3</th><th>%4</th></tr>")
               .arg(tr("Drug"))
               .arg(tr("Dosage in mg"))
               .arg(tr("Last Injection"))
               .arg(tr("Injection Interval")));

    for (auto d : r->depots()) {
        buf.append(QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td></tr>")
                   .arg(d->prescribeableDrugName)
                   .arg(d->dosageInMg)
                   .arg(d->lastInjectionDate.toString(Qt::DefaultLocaleShortDate))
                   .arg(d->injectionIntervalInDays));
    }
    buf.append("</table>");

    buf.append(QString("<p>%1 (%2)</p>").arg("Medication").arg(r->medication().size()));
    buf.append("<table border=\"1\">");
    buf.append(QString("<tr><th>%1</th><th>%2</th></tr>")
               .arg(tr("Molecule"))
               .arg(tr("Dosage in mg")));

    for (auto d : r->medication()) {
        buf.append(QString("<tr><td>%1</td><td>%2</td></tr>")
                   .arg(d->moleculeName)
                   .arg(d->dosageInMg));
    }
    buf.append("</table>");

    return buf.join("\n");
}

QString AgateRecordViewer::formatTableRow(const QString &label, const QString &value) const
{
    return QString("<tr><td>%1</td><td>%2</td></tr>").arg(label).arg(value);
}

QString AgateRecordViewer::formatTableRow(const QString &label, const int value) const
{
    return formatTableRow(label, QString("%1").arg(value));
}

