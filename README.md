# Tree_Cpp
몇몇 트리 자료구조를 C++로 구현한 레포지토리입니다.  
트리 자료구조들에 대한 기본적인 개념은 "C와 C++로 구현하는 자료구조"[1] 책을 참고하였습니다.  
다만 책에서는 직관적인 설명을 위하여 함수적 프로그래밍으로 예제를 구현하거나 구현 없이 개념 소개로 그치는 소재들이 있어, 이들을 C++에서 클래스로 직접 구현해 보고 그 시행착오를 공유하고자 레포지토리를 작성하게 되었습니다.  



## 목차  
[1. 재귀 호출을 이용한 이진 탐색 트리](#1-재귀-호출을-이용한-이진-탐색-트리)  
[2. 반복문을 이용한 이진 탐색 트리](#2-반복문을-이용한-이진-탐색-트리)  
[3. 힙](#3-힙)  
[4. 스플레이 트리](#4-스플레이-트리)  
[5. AVL 트리](#5-avl-트리)   
[6. 레드-블랙 트리 (예정)](#6-레드-블랙-트리)   
[7. B-트리 (예정)](#7-b-트리)  
[8. k-d 트리 (예정)](#8-k-d-트리)  
[9. BVH (예정)](#9-bvh)  



## 1. 재귀 호출을 이용한 이진 탐색 트리
### [개념]
이진 탐색 트리는 평균적으로 O(log(n))의 시간 복잡도로 데이터의 삽입-검색-삭제를 할 수 있도록 한 트리입니다.  
이진 탐색 트리가 만족해야하는 조건을 재귀적으로 설명하면 다음과 같습니다.
    1.루트 노드의 키(key)는 좌측 자식 노드의 키보다는 크고, 우측 자식의 키보다는 작아야 한다.
    2.왼쪽 하위 트리와, 우측 하위 트리도 각기 이진 탐색 트리여야 한다.

#### 탐색 과정
이진 탐색 트리에서는 자식 노드와의 대소 관계를 단서로 이용해 효율적인 탐색이 가능합니다.  
특정 키를 가진 노드를 찾아가는 탐색 과정의 의사코드는 다음과 같습니다.  
```
search(int target_key) {
    if(head == NULL) return;                                                //메소드의 전제 조건 확인

    if(target_key < head.key)       return left_child.search(target_key);   //좌측 자식에서 재귀호출
    else if(head.key < target_key)  return right_child.search(target_key);  //우측 자식에서 재귀호출
    else                            return head;                            //원하는 키의 노드를 찾았음(base case)
}
```
이진 탐색 트리에서 탐색 과정은 삽입-검색-삭제 작업에서 원하는 키의 자리를 찾는 로직으로 사용됩니다.

#### 순회 과정
이진 탐색 트리에서의 깊이우선순회는 재귀를 사용하여 쉽게 구현할 수 있습니다.  
이때 순회를 하며 각 노드에 작업을 수행한다면, 그 작업의 수행 타이밍에 따라 '전위 순회', '중위 순회', '후위 순회'로 나뉘게 됩니다.
1. 전위 순회 : 노드를 처음 방문하는 시점에 작업을 수행합니다.  
2. 중위 순회 : 왼쪽 하위 트리의 방문을 마치는 시점에 작업을 수행합니다.  
3. 후위 순회 : 우측 하위 트리의 방문을 마치는 시점에 작업을 수행합니다.  
```
depth_first_traverse() {
    if(head == NULL) return;            //메소드의 전제조건이자 base case인 경우를 확인

    preorder_traverse_task();           //전위 순회로 수행할 작업
    left_child.depth_first_traverse();  //좌측 자식에서 재귀호출
    inorder_traverse_task();            //중위 순회로 수행할 작업
    right_child.depth_first_traverse(); //우측 자식에서 재귀호출
    postorder_traverse_task();          //후위 순회로 수행할 작업
}
```
이진 탐색 트리에서는 효율적인 탐색이 가능하기에, 모든 노드를 도는 순회는 자주 사용되지 않습니다.  
다만 디버깅을 위해 모든 노드의 내용을 출력해보거나, 모든 노드들의 동적 메모리 공간을 반환해야 하는 트리의 소멸 작업에 사용될 수 있습니다.  
특히 중위 순회는 노드들을 키의 오름차순으로 작업을 수행한다는 특징이 있어 정렬에 응용할 수 있고, 후위 순회는 자신에게 작업을 수행하기 이전에 자신의 모든 자식들에서 먼저 작업을 수행하기에 트리의 소멸 작업에 적합합니다.

---
### [구현]
#### 클래스 멤버 데이터 선언
#### 클래스 멤버 함수 선언
#### 주요 멤버 함수 구현



## 2. 반복문을 이용한 이진 탐색 트리
### [개념]
이진 탐색 트리는 그 정의가 재귀적이므로, 구현 또한 재귀적으로 작성하는 것이 편리하다.  
재귀의 근간이 되는 함수 호출은 인자로 지정된 경우를 제외하고서는 호출 함수와 피호출 함수의 변수들을 격리하기 때문에, 프로그래머가 여러 외부 영향을 고려하지 않고 직관적으로 문제를 해결할 수 있다.  
그러나 이렇게 호출 함수와 피호출 함수의 변수를 격리하는 것에는 당연히 비용이 필요하다. 
함수 호출이 일어나면 피호출 함수로부터 호출 함수의 정보를 보호하기 위해 이들을 메모리의 스택에 저장하고, 또 함수 호출이 끝나면 이들을 레지스터로 다시 돌려놓는 시간이 필요하기 때문이다.
즉 재귀호출은 시간적 비용과 공간적 비용이 따른다고 할 수 있다. 그리고 수많은 데이터를 삽입-검색-삭제를 반복하는 자료구조에서는 재귀 호출의 비용이 치명적으로 다가온다.
따라서 자료구조를 효율적으로 구현하기 위해서는 재귀호출을 while문과 사용자 스택으로 대체하여 작성하여야 한다.

---
### [구현]
#### 클래스 멤버 데이터 선언
#### 클래스 멤버 함수 선언
#### 주요 멤버 함수 구현



## 3. 힙
### [개념]
부모 노드가 자식 노드들보다 크거나(max_heap), 작은(min_heap) 완전 이진 트리.  
트리의 루트 노드는 모든 노드 중 가장 크거나(max_heap), 작은(min_heap) 키를 가진 노드이므로,  
가장 크거나 작은 요소를 반환해야하는 우선순위 큐에 주로 사용된다.  
또한 완전 이진 트리이므로 어레이 구조를 사용하여도 메모리 공간의 낭비가 크지 않아, 간단한 인덱스 연산으로 부모 자식간 이동이 가능하다.

---
### [구현]
#### 클래스 멤버 데이터 선언
#### 클래스 멤버 함수 선언
#### 주요 멤버 함수 구현



## 4. 스플레이 트리
### [개념]
노드에 접근할 때마다 해당 노드를 루트에 가까운 노드에 올리는 자체조정 트리구조.

---
### [구현]
#### 클래스 멤버 데이터 선언
#### 클래스 멤버 함수 선언
#### 주요 멤버 함수 구현



## 5. AVL 트리
### [개념]
이진 탐색 트리에서의 편향 문제를 해결한 균형 트리구조.

---
### [구현]
#### 클래스 멤버 데이터 선언
#### 클래스 멤버 함수 선언
#### 주요 멤버 함수 구현
 


## 6. 레드-블랙 트리
### [개념]
이진 탐색 트리에서의 편향 문제를 해결한 균형 추종 트리구조. 2-3-4 트리를 레드 노드와 블랙 노드로 비교적 간단하게 구현한 것이 특징.    

---
### [구현]
#### 클래스 멤버 데이터 선언
#### 클래스 멤버 함수 선언
#### 주요 멤버 함수 구현



## 7. B-트리
### [개념]
노드 내에 저장되는 데이터의 개수가 일반화된 다진 균형 트리구조.

---
### [구현]
#### 클래스 멤버 데이터 선언
#### 클래스 멤버 함수 선언
#### 주요 멤버 함수 구현



## 8. k-d 트리
### [개념]
다차원 공간에서 점들을 쉽게 탐색할 수 있도록한 트리구조.

---
### [구현]
#### 클래스 멤버 데이터 선언
#### 클래스 멤버 함수 선언
#### 주요 멤버 함수 구현



## 9. BVH
### [개념]
Bounding Volume Hiearchy의 약자. 폴리곤과 같은 기하 개체들을 둘러싼 가상의 바운딩 볼륨을 계층화한 리프 트리구조.

---
### [구현]
#### 클래스 멤버 데이터 선언
#### 클래스 멤버 함수 선언
#### 주요 멤버 함수 구현



## 참고문헌
[1] "C와 C++로 구현하는 자료구조" (주우석 저 / 한빛아카데미 출판)



