#pragma once
namespace sheet {
	class Hash
	{
	private:
		double* mas;
		double* prob_mas;
		double size;
		double all_try = 0;
		double mHash(double);
		double mHash(double, size_t);
	public:
		Hash();
		~Hash();
		Hash(size_t size);
		Hash(const Hash& obj);
		double Get_AllTry();
		void init(size_t size);
		void add(double item);
		void del();
		void del_item(double item);
		bool search(double item);	// обычная
		bool search();				// для пользовательского ввода
		friend std::ostream& operator<<(std::ostream& out, const Hash& obj);
	};
}
