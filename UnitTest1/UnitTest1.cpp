#include "pch.h"
#include "CppUnitTest.h"
#include "../Project14/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AVLTreeTests
{
    TEST_CLASS(AVLTreeTests)
    {
    public:

        TEST_METHOD(TestInsert)
        {
            AVLTree tree;
            tree.insert(30);
            tree.insert(20);
            tree.insert(10);

            AVLNode* root = tree.getRoot();

            Assert::AreEqual(20, root->key);
            Assert::AreEqual(10, root->left->key);
            Assert::AreEqual(30, root->right->key);
        }

        TEST_METHOD(TestRemove)
        {
            AVLTree tree;
            tree.insert(30);
            tree.insert(20);
            tree.insert(10);
            tree.insert(25);

            tree.remove(20);

            AVLNode* root = tree.getRoot();

            Assert::AreEqual(25, root->key);
            Assert::AreEqual(10, root->left->key);
            Assert::AreEqual(30, root->right->key);
        }

        TEST_METHOD(TestInorderTraversal)
        {
            AVLTree tree;
            tree.insert(30);
            tree.insert(20);
            tree.insert(10);
            tree.insert(25);
            tree.insert(40);

            std::ostringstream oss;
            std::streambuf* coutBackup = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());

            tree.printInorder();

            std::cout.rdbuf(coutBackup);

            std::string expectedOutput = "10 20 25 30 40 \n";
            Assert::AreEqual(expectedOutput, oss.str());
        }
        TEST_METHOD(TestPreorderTraversal)
        {
            AVLTree tree;
            tree.insert(30);
            tree.insert(20);
            tree.insert(10);
            tree.insert(25);
            tree.insert(40);

            std::ostringstream oss;
            std::streambuf* coutBackup = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());

            tree.printPreorder();

            std::cout.rdbuf(coutBackup);

            std::string expectedOutput = "20 10 30 25 40 \n";
            Assert::AreEqual(expectedOutput, oss.str());
        }

        TEST_METHOD(TestPostorderTraversal)
        {
            AVLTree tree;
            tree.insert(30);
            tree.insert(20);
            tree.insert(10);
            tree.insert(25);
            tree.insert(40);

            std::ostringstream oss;
            std::streambuf* coutBackup = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());

            tree.printPostorder();

            std::cout.rdbuf(coutBackup);

            std::string expectedOutput = "10 25 40 30 20 \n";
            Assert::AreEqual(expectedOutput, oss.str());
        }
    };
        
 }
