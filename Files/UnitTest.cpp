#include "pch.h"
#include "CppUnitTest.h"
#include "E:\WORK\VS\VisualStudio2019_projects\drweb\Lesta.h"
#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RingBufferUnitTest
{
	TEST_CLASS(BufferAUnitTest)
	{
	public:
		TEST_METHOD(WriteAndRead)
		{
			RingBufferArray<int, 3> BufferA;

			BufferA.Write(2);
			BufferA.Write(3);
			
			Assert::AreEqual(BufferA.Read(), 3);
			
		}
		
 		TEST_METHOD(Override)
		{
			RingBufferArray<int, 3> BufferA;

			BufferA.Write(2);
			BufferA.Write(3);
			BufferA.Write(4);
			BufferA.Write(5);

			Assert::AreEqual(BufferA.Delete(), 3);
		}
		TEST_METHOD(Empty)
		{
			RingBufferArray<int, 3> BufferA;

			try
			{
				BufferA.Read();
			}
			catch (const std::runtime_error& RE)
			{
				Assert::AreEqual(RE.what(), "Buffer is empty. Can't read.");
			}

			try 
			{
				BufferA.Delete();
			}
			catch (const std::runtime_error& RE)
			{
				Assert::AreEqual(RE.what(), "Buffer is empty. Can't delete.");
			}
		}

	};

	TEST_CLASS(BufferVUnitTest)
	{
	public:
		TEST_METHOD(WriteAndRead)
		{
			RingBufferVector<int> BufferV(3);

			BufferV.Write(2);
			BufferV.Write(3);

			Assert::AreEqual(BufferV.Read(), 3);
			Assert::AreEqual(BufferV.Read(), 2);
		}
		TEST_METHOD(Empty)
		{
			RingBufferVector<int> BufferV(3);

			try
			{
				BufferV.Read();
			}
			catch (const std::runtime_error& RE)
			{
				Assert::AreEqual(RE.what(), "Buffer is empty. Can't read.");
			}
		}
	};
}
