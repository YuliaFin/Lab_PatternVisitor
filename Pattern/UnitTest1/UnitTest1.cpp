#include "pch.h"
#include <stdio.h>
#include "CppUnitTest.h"
#include "..\Pattern\Pattern.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(Test_for_struct_Number)
	{
	public:
		
		TEST_METHOD(TestConstuctorNumber)
		{	
			srand(time(NULL));
			Number* number = new Number(static_cast <double> (rand()));
			double num = number->value(); 
			Assert::IsTrue(number->value() == num);
		}

		TEST_METHOD(TestEvaluateNumber)
		{
			srand(time(NULL));
			Number* number = new Number(static_cast <double> (rand()));
			double num = number->value();
			Assert::IsTrue(number->evaluate() == num);
		}
	};

	TEST_CLASS(Test_struct_BinaryOperation)
	{
	public:

		TEST_METHOD(TestConstuctorBinaryOperation)
		{
			Number* n32 = new Number(32.0);
			Number* n16 = new Number(16.0);
			BinaryOperation* minus = new BinaryOperation(n32, BinaryOperation::MINUS, n16);
			Assert::IsTrue(minus->left() == n32 && minus->operation() == BinaryOperation::MINUS && minus->right() == n16);
		}

		TEST_METHOD(TestBinaryOperationPlus) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (rand()));
			Number* number2 = new Number(static_cast <double> (rand()));
			BinaryOperation* plus = new BinaryOperation(number1, BinaryOperation::PLUS,number2);
			Assert::IsTrue(plus->evaluate() == number1->value() + number2->value());
		}

		TEST_METHOD(TestBinaryOperationMinus) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (rand()));
			Number* number2 = new Number(static_cast <double> (rand()));
			BinaryOperation* minus = new BinaryOperation(number1, BinaryOperation::MINUS, number2);
			Assert::IsTrue(minus->evaluate() == number1->value() - number2->value());
		}

		TEST_METHOD(TestBinaryOperationDivision) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (rand()));
			Number* number2 = new Number(static_cast <double> (rand()));
			BinaryOperation* div = new BinaryOperation(number1, BinaryOperation::DIV, number2);
			Assert::IsTrue(div->evaluate() == number1->value() / number2->value());
		}

		TEST_METHOD(TestBinaryOperationDivisionByZero) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (rand()));
			Number* n0 = new Number(0.0);
			BinaryOperation* div_z = new BinaryOperation(number1, BinaryOperation::DIV, n0);
			Assert::ExpectException<std::invalid_argument>([div_z]() {div_z->evaluate(); });

		}

		TEST_METHOD(TestBinaryOperationMultiplication) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (rand()));
			Number* number2 = new Number(static_cast <double> (rand()));
			BinaryOperation* mul = new BinaryOperation(number1, BinaryOperation::MUL, number2);
			Assert::IsTrue(mul->evaluate() == number1->value() * number2->value());
		}

	};


	TEST_CLASS(Test_struct_FunctionCall)
	{
	public:
		TEST_METHOD(TestConstructorFuncCall_SQRT) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (rand()));
			FunctionCall* callSqrt = new FunctionCall("sqrt", number1);
			Assert::IsTrue(callSqrt->arg() == number1 && callSqrt->name() == "sqrt");
		}

		TEST_METHOD(TestConstructorFuncCall_abs) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (rand()));
			FunctionCall* callSqrt = new FunctionCall("abs", number1);
			Assert::IsTrue(callSqrt->arg() == number1 && callSqrt->name() == "abs");
		}

		TEST_METHOD(TestEvaluteFuncCall_SQRT) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (rand()));
			FunctionCall* callSqrt = new FunctionCall("sqrt", number1);
			Assert::IsTrue(callSqrt->evaluate() == sqrt(number1->value()));
		}

		TEST_METHOD(TestEvaluteNegativeSQRTFuncCall) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (-rand()));
			FunctionCall* callSqrt = new FunctionCall("sqrt", number1);
			Assert::ExpectException<std::invalid_argument>([callSqrt]() {callSqrt->evaluate(); });

		}
		TEST_METHOD(TestEvaluteFuncCall_abs) {
			srand(time(NULL));
			Number* number1 = new Number(static_cast <double> (-rand()));
			FunctionCall* call_abs = new FunctionCall("abs", number1);
			Assert::IsTrue(call_abs->evaluate() == abs(number1->value()));
		}
	};

	TEST_CLASS(Test_struct_Variable)
	{
	public:
		TEST_METHOD(TestConstructorValue) {
			Variable* variable = new Variable("variable");
			Assert::IsTrue(variable->name() == "variable");
		}


		TEST_METHOD(TestEvaluateValue) {
			Variable* variable = new Variable("variable");
			Assert::IsTrue(variable->evaluate() == 0.0);
		}

	};

	TEST_CLASS(Test_struct_CopySyntaxTree)
	{
	public:

		TEST_METHOD(CopyNumber)
		{
			CopySyntaxTree tree_copy;
			Number num(32.0);
			Expression* exp = num.transform(&tree_copy);
			Number* result = dynamic_cast<Number*>(exp);
			Assert::IsNotNull(result);
			Assert::AreEqual(32.0, result->value());
		}

		TEST_METHOD(CopyVariable)
		{
			CopySyntaxTree tree_copy;
			Variable variable("x");
			Expression* exp = variable.transform(&tree_copy);
			Variable* result = dynamic_cast<Variable*>(exp);
			Assert::IsNotNull(result);
			Assert::AreEqual(std::string("x"), result->name());
		}
	};
}
