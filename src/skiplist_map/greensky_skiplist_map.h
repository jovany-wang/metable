#pragma once

#include "include/sl_map.h"

#include "skiplist_map.h"

namespace metable {

template <typename KeyType, typename ValueType>
class GreenSkySkiplistMap : public SkiplistMap<KeyType, ValueType> {
public:
  virtual bool Put(const KeyType &key, const ValueType &value) override;

  virtual bool Get(const KeyType &key, ValueType *value) override;

  virtual bool Remove(const KeyType &key) override;

  virtual bool Contains(const KeyType &key) override;

  /// The desctuctor of this class.
  ~GreenSkySkiplistMap() = default;

private:
  sl_map_gc<KeyType, ValueType> data_;
};

} // namespace metable
