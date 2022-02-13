#pragma once

namespace metable {

class Field {
public:

private:
    std::string field_name_;
    FieldType type_;
    FieldValue value_;
};

class TableSchema final {
public:

private:
    std::vector<Field> all_fields_;
};

} // namespace metable
