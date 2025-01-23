#include "BitArray.h"
#include <sstream>
#include <limits>

BitArray::BitArray() : m_size(0) {}

BitArray::~BitArray() {}

BitArray::BitArray(int num_bits, unsigned long value) : m_size(num_bits) {
    if (num_bits < 0) throw std::invalid_argument("BitArray constructor: num_bits < 0");
    reallocate();
    for (int i = 0; i < std::min(num_bits, 8 * (int)sizeof(value)); ++i) {
        set(i, (value >> i) & 1);
    }
}

BitArray::BitArray(const BitArray& b) : m_data(b.m_data), m_size(b.m_size) {}

void BitArray::swap(BitArray& b) {
    std::swap(m_data, b.m_data);
    std::swap(m_size, b.m_size);
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        BitArray temp(b);
        swap(temp);
    }
    return *this;
}

void BitArray::resize(int num_bits, bool value) {
    if (num_bits < 0) throw std::invalid_argument("BitArray::resize: num_bits < 0");
    int old_size = m_size;
    m_size = num_bits;
    reallocate();
    if (num_bits > old_size) {
        for (int i = old_size; i < num_bits; ++i) {
            set(i, value);
        }
    }
}

void BitArray::clear() {
    m_data.clear();
    m_size = 0;
}

void BitArray::push_back(bool bit) {
    resize(m_size + 1);
    set(m_size - 1, bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (size() != b.size()) throw std::invalid_argument("BitArray::operator&=: different sizes");
    for (size_t i = 0; i < m_data.size(); ++i) {
        m_data[i] &= b.m_data[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (size() != b.size()) throw std::invalid_argument("BitArray::operator|=: different sizes");
    for (size_t i = 0; i < m_data.size(); ++i) {
        m_data[i] |= b.m_data[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (size() != b.size()) throw std::invalid_argument("BitArray::operator^=: different sizes");
    for (size_t i = 0; i < m_data.size(); ++i) {
        m_data[i] ^= b.m_data[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n < 0) throw std::invalid_argument("BitArray::operator<<=: negative shift");
    if (n >= m_size) {
        reset();
        return *this;
    }
    for (int i = m_size - 1; i >= n; --i) {
        set(i, (*this)[i - n]);
    }
    for (int i = 0; i < n; ++i) {
        set(i, false);
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0) throw std::invalid_argument("BitArray::operator>>=: negative shift");
    if (n >= m_size) {
        reset();
        return *this;
    }
    for (int i = 0; i < m_size - n; ++i) {
        set(i, (*this)[i + n]);
    }
    for (int i = m_size - n; i < m_size; ++i) {
        set(i, false);
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray temp(*this);
    return temp <<= n;
}

BitArray BitArray::operator>>(int n) const {
    BitArray temp(*this);
    return temp >>= n;
}

BitArray& BitArray::set(int n, bool val) {
    check_index(n);
    auto [block, offset] = get_block_and_offset(n);
    if (val) {
        m_data[block] |= (1ULL << offset);
    } else {
        m_data[block] &= ~(1ULL << offset);
    }
    return *this;
}

BitArray& BitArray::set() {
    std::fill(m_data.begin(), m_data.end(), std::numeric_limits<unsigned long long>::max());
    int remainder = m_size % BITS_PER_BLOCK;
    if (remainder) {
        m_data.back() &= (1ULL << remainder) - 1;
    }
    return *this;
}

BitArray& BitArray::reset(int n) {
    return set(n, false);
}

BitArray& BitArray::reset() {
    std::fill(m_data.begin(), m_data.end(), 0);
    return *this;
}

bool BitArray::any() const {
    return std::any_of(m_data.begin(), m_data.end(), [](unsigned long long block) { return block != 0; });
}

bool BitArray::none() const {
    return !any();
}

BitArray BitArray::operator~() const {
    BitArray temp(*this);
    for (auto& block : temp.m_data) {
        block = ~block;
    }
    temp.reallocate(); // Ensure extra bits are zeroed.
    return temp;
}

int BitArray::count() const {
    int total = 0;
    for (auto block : m_data) {
        while (block) {
            block &= (block - 1);
            ++total;
        }
    }
    return total;
}

bool BitArray::operator[](int i) const {
    check_index(i);
    auto [block, offset] = get_block_and_offset(i);
    return (m_data[block] >> offset) & 1;
}

int BitArray::size() const {
    return m_size;
}

bool BitArray::empty() const {
    return m_size == 0;
}

std::string BitArray::to_string() const {
    std::string result(m_size, '0');
    for (int i = 0; i < m_size; ++i) {
        if ((*this)[i]) result[m_size - i - 1] = '1';
    }
    return result;
}

void BitArray::check_index(int index) const {
    if (index < 0 || index >= m_size) throw std::out_of_range("BitArray: index out of range");
}

void BitArray::reallocate() {
    int required_blocks = (m_size + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK;
    m_data.resize(required_blocks, 0);
}

std::pair<int, int> BitArray::get_block_and_offset(int bit_index) const {
    return { bit_index / BITS_PER_BLOCK, bit_index % BITS_PER_BLOCK };
}

bool operator==(const BitArray& a, const BitArray& b) {
    return a.m_size == b.m_size && a.m_data == b.m_data;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result |= b2;
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result ^= b2;
    return result;
}
