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
    VectorInt(const VectorInt& other){
    arr = nullptr;
    arr = other.arr;
    size = other.size;
    capacity = other.capacity;
    }
    VectorInt(VectorInt& other) {
        arr = nullptr;
        arr = other.arr;
        size = other.size;
        capacity = other.capacity;
        other.arr = nullptr;
        other.size = other.capacity = 0;
    }
    VectorInt(VectorInt&& other)noexcept {
        arr = nullptr;
        arr = other.arr;
        size = other.size;
        capacity = other.capacity;
        other.arr = nullptr;
        other.size = other.capacity = 0;
    }
    VectorInt& operator=(VectorInt& other) {
        if (this != &other) {
            delete[] arr;
            arr = other.arr;
            size = other.size;
            capacity = other.capacity;
            other.arr = nullptr;
            other.size = other.capacity = 0;
        }
        return *this;
    }
    VectorInt& operator= (VectorInt&& other) noexcept {
        if (this != &other) {
            delete[] arr;
            arr = other.arr;
            size = other.size;
            capacity = other.capacity;
            other.arr = nullptr;
            other.size = other.capacity = 0;
        }
        return *this;
    }
    void pushFront(const int var){
        if(this->size == this->capacity)
            add_capacity();
        int *var_arr = this->arr;
        arr = new int [this->capacity];
        for(size_t idx_i = 0; idx_i < this->size; ++idx_i){
            arr[idx_i + 1] = var_arr[idx_i];
        }
        delete[] var_arr;
        arr[0] = var;
        ++this->size;
    }
    void insert(const int var,const int index){
        if(at(index)){
            if(this->size == this->capacity)
                add_capacity();
            
            int *var_arr = this->arr;
            arr = new int [capacity];
            size_t idx_k = 0;
            for(size_t idx_i = 0; idx_i <= size; ++idx_i){
                if(idx_i == index)
                    ++idx_i;
                arr[idx_i] = var_arr[idx_k];
                ++idx_k;
            }
            delete[] var_arr;
            arr[index] = var;
            ++this->size;
        }else
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
/*
Большое спасибо вам, вы один из лучших преподавателей на этом курсе.
Грамотно и четко объясняете, что, зачем и почему.
Очень приятно каждый раз получать от вас замечания и исправлять их, получая новые знания. 
*/
int main() {
    try {
        VectorInt arr1(10);
        for (size_t idx_i = 0; idx_i < arr1.get_capacity(); ++idx_i) {
            arr1.pushBack(idx_i);
        }
        std::cout << arr1 << std::endl;
        VectorInt arr2;
        arr2 = arr1;
        std::cout << arr2 << std::endl;
        const VectorInt arr3(arr2);
        std::cout << arr3 << std::endl;
        VectorInt arr4(arr3);
        std::cout << arr3 << std::endl;
        
    }
    catch(const ExceptionVectorInt &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}