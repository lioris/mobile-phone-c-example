/********************************MODULE LIST*********************************
In this module the Node structure  is defined, and the list implemention is defined.

In this module you can find the functions that work with linked list
**************************************************************************/

#ifndef __list_H			//מניעת הכללה כפולה
#define __list_H

struct Node;
typedef void* ElementType;		//הגדרת הטיפוס עבור הרשימה
typedef struct Node *PtrToNode;	// מצביע לרשומה
typedef PtrToNode List;			// מצביע לרשימה
typedef PtrToNode Position;		// מצביע לאיבר ברשימה

List MakeEmpty(List L);		//אתחול רשימה
Position Header(List L);		//החזרת כתובת הכותר
Position First(List L);		//כתובת הצומת הראשונה
Position Advance(Position P);	//כתובת הצומת הבאה
ElementType Retrieve(Position P); 	//אחזור המידע שבצומת המוצבעת
int IsEmpty(List L);		//האם הרשימה ריקה
int IsLast(Position P, List L);		//האם איבר אחרון ברשימה
Position Find(ElementType X, List L);	//X מציאת הצומת הראשונה עם המידע 
void Delete(ElementType X, List L);	//X הסרת הצומת הראשונה עם המידע
Position FindPrevious(ElementType X, List L); // והחזרת כתובת הצומת שלפניהX מציאת הצומת הראשונה עם
void Insert(ElementType X, List L, Position P);//הוספת איבר חדש לרשימה לאחר הצומת המוצבעת
void DeleteList(List L);		//שחרור הרשימה ואיפוסה כך שניתן לעבוד עליה מחדש


Position deleteAfter(ElementType X, List list); // מחיקת איבר מהרשימה לאחר הצומת המוצבעת ללא הקצאת זיכרון
void InsertLats(ElementType X, List L);//הוספת איבר חדש לסוף הרשימה
ElementType deleteLast(List list);

#endif  /* _List_H */
