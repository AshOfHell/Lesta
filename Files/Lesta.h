#pragma once

#include <iostream>
#include <vector>
#include <array>

template <typename T>
class RingBufferVector
{
    private:
        std::vector<T> Buffer{ 0 };
        size_t Size{ 0 };
        size_t El{ 0 };
        size_t Count{0};

    public:
        RingBufferVector(size_t Volume) : Size(Volume), El(0), Count(0)
        {
            Buffer.resize(Size);
        }
        
        ~RingBufferVector(){}

        //Add item
        void Write(T Item)
        {
            if (El < Size)
            {
                Buffer.at(El) = Item;
                El++;
                if (Count < Size)
                    Count++;
            }
            else
            {
                Buffer.at(0) = Item;
                El = 1;
                if (Count < Size)
                    Count++;
            }
            return;
        }
        
        //Read and delete last item
        T Read()
        {
            if (IsEmpty())
            {
                throw std::runtime_error("Buffer is empty. Can't read.");
            }
            else
            {
                El--;
                T Item = Buffer.at(El);
                Count--;
                return Item;
            }
        }
        
        //Empty check
        bool IsEmpty()
        {
            return Count == 0;
        }

        //Full check
        bool IsFull()
        {
            if (!IsEmpty())
                return (Count % Size) == 0;
            else return 0;
        }

        //Clear buffer
        void Clear()
        {
            Buffer.clear();
            El = 0;
            Count = 0;
            return;
        }
};

template <typename T, size_t Volume>
class RingBufferArray
{
    private:
        std::array<T, Volume> Buffer;
        size_t Head{ 0 };
        size_t Tail{ 0 };
        size_t Count{ 0 };
    public:
        
        RingBufferArray() {}
        ~RingBufferArray() {}
        
        //Add item
        void Write(T Item)
        {
            Buffer[Head] = Item;
            Head = (Head + 1) % Volume;
            if (IsFull())
                Tail = (Tail + 1) % Volume;
            if (Count < Volume)
                Count++;
        }
        
        //Read last item without deletion
        T Read()
        {
            if (IsEmpty())
            {
                throw std::runtime_error("Buffer is empty. Can't read.");
            }
            else if (Head == 0) 
            {
                size_t Prev = Volume - 1;
                T Item = std::move(Buffer[Prev]);
                return Item;
            }
            else 
            {
                size_t Prev = Head - 1;
                T Item = Buffer[Prev]; 
                return Item;
            }
        }
        
        //Read and count as deleted oldest item
        T Delete()
        {
            if (IsEmpty())
            {
                throw std::runtime_error("Buffer is empty. Can't delete.");
            }
            else 
            {
                T Item = std::move(Buffer[Tail]); 
                Count--;
                Tail = (Tail + 1) % Volume; 
                return Item;
            }
        }

        //Empty check
        bool IsEmpty()
        {
            return Count == 0;
        }
        
        //Full check
        bool IsFull()
        {
            return Count == Volume;
        }

        //Clear buffer
        void Clear()
        {
            Buffer.fill(0);
            Head = 0;
            Tail = 0;
            Count = 0;
        }
};
