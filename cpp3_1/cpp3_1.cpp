#include <iostream>
#include <string>
#include <exception>

class ExceptionVectorInt : std::exception {
private:
    std::string whatStr;
public:
    ExceptionVectorInt (std::string &&whatStr) noexcept : whatStr(std::move(whatStr)) {}
    ExceptionVectorInt (const std::string &whatStr) noexcept : whatStr(whatStr) {}
    ~ExceptionVectorInt () noexcept = default;
    
    const char *what() const noexcept override{
        return whatStr.c_str();
    }
};

class VectorInt{
private:
    int *arr;
    int size;
    int capacity;
    void add_capacity(){
        this->capacity *= 2;
        int *var = arr;
        arr = new int [this->capacity];
        for(size_t idx_i = 0; idx_i < this->size; ++idx_i){
            arr[idx_i] = var[idx_i];
        }
        delete[] var;
    }
    void remove_capacity(){
        this->capacity = this->size;
        int *var = arr;
        arr = new int [this->capacity];
        for(size_t idx_i = 0; idx_i < this->size; ++idx_i){
            arr[idx_i] = var[idx_i];
        }
        delete[] var;
    }
public:
    VectorInt(){
        capacity = 1;
        size = 0;
        this->arr = new int [capacity];
    }
    VectorInt(const int capacity){
        this->size = 0;
        this->capacity = capacity;
        this->arr = new int [capacity];
    }
    ~VectorInt(){delete[] arr;}
    void pushBack(const int var){
        if(this->size == this->capacity)
            add_capacity();
            arr[this->size] = var;
            ++this->size;
    }
    VectorInt(const VectorInt &) = delete;
    VectorInt &operator= (const VectorInt&) = delete;
    void pushFront(const int var) {
        if (this->size == 0)
            pushBack(var);
        else {
            if (this->size == this->capacity)
                add_capacity();
            for (int idx_i = this->size; idx_i > 0; --idx_i) {
                arr[idx_i] = arr[idx_i - 1];
            }
            arr[0] = var;
            ++this->size;
        }
    }
    void insert(const int var, const int index) {
        if (index == 0 || index == size) 
            pushBack(var);
        else if (at(index)) {
            if (this->size == this->capacity)
                add_capacity();
            size_t idx_k = 0;
            for (size_t idx_i = 0; idx_i <= this->size; ++idx_i) {
                if (idx_i == index)
                    continue;
                arr[idx_i] = arr[idx_k];
                ++idx_k;
            }
            arr[index] = var;
            ++this->size;
        }
        else
            throw ExceptionVectorInt("Wrong index, array size is smaller <insert>");
    }
    bool at(const int index){
        if(index <= size && index >= 0)
            return true;
        return false;
    }
    const bool at(const int index)const{
        if(index <= size && index >= 0)
            return true;
        return false;
    }
    int &operator[] (const int index){
        if(!at(index)){
            throw ExceptionVectorInt("Wrong index, array size is smaller <[]>");
        }
        return arr[index];
    }
    const int &operator[]  (const int index)const {
        if(!at(index)){
            throw ExceptionVectorInt("Wrong index, array size is smaller <[]>");
        }
        return arr[index];
    }
    int get_size() const{return this->size;}
    int get_capacity() const{return this->capacity;}
    friend std::ostream &operator<< (std::ostream &out,const VectorInt & var){
        for(size_t idx_i = 0; idx_i < var.get_size(); ++idx_i ){
            out << var[idx_i] << '\t';
        }
        return out;
    }
};

int main(){
try
{
    VectorInt arr(10);
    std::cout << arr.get_size() << '\t' << arr.get_capacity() << std::endl;
    arr.pushBack(2);
    std::cout << arr << std::endl;
    arr.pushFront(1);
    std::cout << arr << std::endl;
    arr.insert(99,1);
    std::cout << arr.get_size() << '\t' << arr.get_capacity() << std::endl;
    std::cout << arr << std::endl;
    // arr.insert(10,11);
    std::cout << arr[0] << std::endl;
    // std::cout << arr[10] << std::endl;
}
catch(const ExceptionVectorInt &e)
{
    std::cerr << e.what() << '\n';
}

 
}