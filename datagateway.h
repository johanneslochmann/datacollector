#pragma once

#include "abstractdatagateway.hxx"

#include <QSqlRecord>

#include "datacollector.hxx"

class Storable;

template<typename T>
class DataGateway: public AbstractDataGateway {
public:
    using DataType = T;
    using DataTypeSPtr = std::shared_ptr<DataType>;
    using ContainerT = std::vector<std::shared_ptr<DataType>>;

    DataGateway()
        : AbstractDataGateway()
    {}

    ContainerT loadAll() {
        ContainerT buf;

        auto qry = DataCollector::get()->prepareAndPerformQuery(loadAllQueryText(), false);

        while(qry.next()) {
            auto t = std::make_shared<DataType>();
            parse(t, qry.record());
            buf.push_back(t);
        }

        return buf;
    }

    DataTypeSPtr loadById(const int id) {
        auto qry = DataCollector::get()->prepareQuery(loadByIdQueryText());
        qry.bindValue(":id", id);
        DataCollector::get()->performQueryWithExpectedSize(qry, 1, false);
        qry.next();
        auto t = std::make_shared<DataType>();
        parse(t, qry.record());
        return t;
    }

protected:
    virtual QString loadAllQueryText() const = 0;
    virtual QString loadByIdQueryText() const { return "load by id not supported."; }
    virtual void parse(std::shared_ptr<DataType> t, const QSqlRecord& rec) = 0;
};
