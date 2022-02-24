#pragma once

namespace metable {

/// The basic interface for skiplist map, which defines the genernal
/// opeations for a random serach map.
template <typename KeyType, typename ValueType>
class SkiplistMap {
public:

  /// Put an key value pair into this skiplist map.
  ///
  /// @Return: True if successed to put the key value pair into this
  /// skiplist map, otherwise returns false.
  virtual bool Put(const KeyType &key, const ValueType &value) = 0;

  /// Get a value from this skiplist map by the given key.
  ///
  /// @Return: Returns true if successed to get and the output parameter
  /// will be filled in the value of this key. Otherwise it's false and the
  /// value will not be filled anything.
  virtual bool Get(const KeyType &key, ValueType *value) = 0;
  
  /// Remove a key value pair from this skiplist.
  ///
  /// @Return: Return true if successed to remove it, otherwise it's false.
  virtual bool Remove(const KeyType &key) = 0;

   /// Query if this skiplist map contains the key value pair by the given key.
   ///
   /// @Return: Return true if it contains the key value pair by the given key,
   /// otherwise returns false.
  virtual bool Contains(const KeyType &key) = 0;
  
  /// The desctuctor of this class.
  virtual ~SkiplistMap() = default;
};

} // namespace metable
