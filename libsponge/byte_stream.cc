#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    : buffer_(), capacity_(capacity), bytes_written_(0), bytes_read_(0), end_input_(false), _error(false){}

size_t ByteStream::write(const string &data) {
    size_t w_size = min(data.size(), remaining_capacity());
    for(size_t i=0; i<w_size; i++) buffer_.push_back(data[i]);
    bytes_written_ += w_size;
    return w_size;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t peek_size = min(len, buffer_.size());
    return string(buffer_.begin(), buffer_.begin() + peek_size);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t pop_size = min(len, buffer_.size());
    for(size_t i=0; i<pop_size; i++) buffer_.pop_front();
    bytes_read_ += pop_size;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string res = peek_output(len);
    pop_output(len);
    return res;
}

void ByteStream::end_input() {
    end_input_ = true;
}

bool ByteStream::input_ended() const { 
    return end_input_; 
}

size_t ByteStream::buffer_size() const { 
    return buffer_.size(); 
}

bool ByteStream::buffer_empty() const { 
    return buffer_.empty(); 
}

bool ByteStream::eof() const { 
    return buffer_.empty() && end_input_; 
}

size_t ByteStream::bytes_written() const { 
    return bytes_written_;
}

size_t ByteStream::bytes_read() const { 
    return bytes_read_; 
}

size_t ByteStream::remaining_capacity() const { 
    return capacity_ - buffer_.size();
}
