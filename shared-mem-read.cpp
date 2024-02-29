#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>

bool
shared_mem_exists(const char* filename)
{
   using namespace boost::interprocess;
	try{
		shared_memory_object shm (open_only, filename, read_write);
	}
	catch(const std::exception & ex) {return false;}
	return true;
}
int main(int argc, char *argv[])
{
   using namespace boost::interprocess;

      //Open already created shared memory object.
      while(!shared_mem_exists("Writer_has_written")){printf("Waiting\n");};
      printf("%d\n",shared_mem_exists("MySharedMemory"));
      shared_memory_object shm (open_only, "MySharedMemory", read_write);

      //Map the whole shared memory in this process
      mapped_region region(shm, read_write);

      //Check that memory was initialized to 1
      char *mem = static_cast<char*>(region.get_address());
      for(std::size_t i = 0; i < region.get_size(); ++i)
         if(*mem++ != 1)
	 {
		 //Error checking memory
		 printf("Not all one!\n");
		 return 1;
	 }
      printf("Read\n");
      fflush(stdout);
      shared_memory_object shm_signal (create_only, "Reader_has_read", read_write);
   return 0;
}
