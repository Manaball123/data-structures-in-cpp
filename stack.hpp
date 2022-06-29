


namespace DS
{

	class Stack 
	{
	
		template <class dtype>
		class Node
		{

			dtype data;
			void* last_ptr;

			Node();
			~Node();

		};


		Stack();
		~Stack();

		void Push(dtype data);
		dtype Pop();




		Stack()
		{

		}










	};
}