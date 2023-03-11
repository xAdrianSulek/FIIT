using System;


namespace TryingShit
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            AVLTree avlTree = new AVLTree();
            avlTree.add(25);
            avlTree.add(70);
            avlTree.add(20);
            avlTree.add(10);
            avlTree.add(15);
            avlTree.display();
        }
    }


    /// <summary>
    /// KYSNEM SA FR
    /// </summary>
    class AVLTree
    {

        internal class Node
        {
            public int height;
            public int data;
            public Node left;
            public Node right;

            public Node(int data)
            {
                this.data = data;
                
            }
            public Node()
            {
            }
        }
        Node parent;
        
        public void add(int data)
        {
            
            if (parent == null)
            {
                parent = new Node(data);
            }
            else
            {
                insert(parent,data);
            }
        }
        
        
        public void insert(Node currentNode, int data)
        {
            if (data < currentNode.data)
            {
                if (currentNode.left == null)
                {
                    currentNode.left = new Node(data);   
                }
                else
                {
                    insert(currentNode.left, data);
                    currentNode = balance(currentNode);
                }
            }
            
            else if (data > currentNode.data)
            {
                if (currentNode.right == null)
                {
                    currentNode.right = new Node(data);
                }
                else
                {
                    insert(currentNode.right, data);
                    currentNode = balance(currentNode);
                }
            }
            
        }
        
        
        public Node balance(Node node)
        {
            int HeightDiff = heightDifference(node);
            
            if (HeightDiff > 1)
            {
                if (heightDifference(node.left) > 0)
                {
                    node = rotationLeftLeft(node);
                }
                else
                {
                    node = rotationLeftRight(node);
                }
            }
            
            else if (HeightDiff < -1)
            {
                if (heightDifference(node.right) > 0)
                {
                    node = rotationRightLeft(node);
                }
                else
                {
                    node = rotationRightRight(node);
                }
            }

            return node;
        }
        

        public int Height()
        {
            return HeightHelper(parent);
        }


        public int HeightHelper(Node node)
        {
            int height = 0;
            if (node != null)
            {
                int left = HeightHelper(node.left);
                int right = HeightHelper(node.right);
                height = Math.Max(left, right) + 1;
            }
            return height;
        }

        
        /// 
        /// Mozno bude lepsie storovat height v kazdom note. tato rekurzia moze trvat dlho
        /// 
        public int heightDifference(Node node)
        {
            int left = HeightHelper(node.left);
            int right = HeightHelper(node.right);
            int heightDiff = left - right;
            return heightDiff;
        }
        
        
        
        public void displayHeight()
        {
            Console.WriteLine(Height());
        }
        
        
        
        public void display()
        {
            if (parent == null)
            {
                Console.WriteLine("Strom je prazdny");
            }
            else
            {
                displayFromLevels(parent);
            }
        }

        public void displayFromLevels(Node node)
        {
            
            Console.Write(node.data + " ");
            Console.Write(Height()+ "HEIGHT ");

            if (node.left != null)
            {
                Console.Write(node.left.data + "L");
                displayFromLevels(node.left);
            }
            if (node.right != null)
            {
                Console.Write(node.right.data + "R");
                displayFromLevels(node.right);
            }
        }



        public Node rotationRightRight(Node parentOfTriangle)
        {
            Node rotation = parentOfTriangle.right;
            parentOfTriangle.right = rotation.left;
            rotation.left = parentOfTriangle;
            return rotation;
        }
        
        public Node rotationRightLeft(Node parentOfTriangle)
        {
            Node rotation = parentOfTriangle.right;
            parentOfTriangle.right = rotationLeftLeft(rotation);
            return rotationRightRight(parentOfTriangle);
        }
        
        public Node rotationLeftLeft(Node parentOfTriangle)
        {
            Node rotation = parentOfTriangle.left;
            parentOfTriangle.left = rotation.right;
            rotation.right = parentOfTriangle;
            return rotation;
        }
        
        public Node rotationLeftRight(Node parentOfTriangle)
        {
            Node rotation = parentOfTriangle.left;
            parentOfTriangle.left = rotationRightRight(rotation);
            return rotationLeftLeft(parentOfTriangle);
        }
        
    }
}