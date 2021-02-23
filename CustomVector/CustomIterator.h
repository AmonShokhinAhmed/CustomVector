class CustomIterator {
public:
	CustomIterator() {

	}
	CustomIterator operator+(const int&) {
		return CustomIterator();
	}
};