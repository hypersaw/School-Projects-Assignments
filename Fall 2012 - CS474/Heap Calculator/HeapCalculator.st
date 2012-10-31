<?xml version="1.0"?>

<st-source>
<time-stamp>From VisualWorks® Personal Use Edition, 7.9 of May 11, 2012 on October 30, 2012 at 9:13:42 PM</time-stamp>


<component-created>
<name>HeapCalculator</name> <type>package</type>
</component-created><!-- Package HeapCalculator* -->


<component-created>
<name>HeapCalculator</name> <type>package</type>
</component-created>

<class>
<name>BinaryHeap</name>
<environment>Smalltalk</environment>
<super>Core.Object</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>root last </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category></category>
<attributes>
<package>HeapCalculator</package>
</attributes>
</class>

<comment>
<class-id>BinaryHeap</class-id>
<body>BinaryHeap has not been commented.  The comment should state the purpose of the class and also explain any unobvious aspects of the implementation. Instance Variables	last	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of last	root	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of root</body>
</comment>

<class>
<name>Queue</name>
<environment>Smalltalk</environment>
<super>Core.Object</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>root count </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category></category>
<attributes>
<package>HeapCalculator</package>
</attributes>
</class>

<comment>
<class-id>Queue</class-id>
<body>Queue has not been commented.  The comment should state the purpose of the class and also explain any unobvious aspects of the implementation. Instance Variables	root	&lt;BinaryNode&gt;	description of root</body>
</comment>

<class>
<name>BinaryNode</name>
<environment>Smalltalk</environment>
<super>Core.Object</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>data leftChild rightChild parent </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category></category>
<attributes>
<package>HeapCalculator</package>
</attributes>
</class>

<comment>
<class-id>BinaryNode</class-id>
<body>Node that contains data and pointers to a parent node, left child, and right child.Instance Variables	data	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	Data contained in Node.	leftChild	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	The left child of Node.	parent	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	The parent of Node.	rightChild	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	The right child of Node.</body>
</comment>

<class>
<name>TertiaryNode</name>
<environment>Smalltalk</environment>
<super>Core.Object</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>data parent leftChild middleChild rightChild </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category></category>
<attributes>
<package>HeapCalculator</package>
</attributes>
</class>

<comment>
<class-id>TertiaryNode</class-id>
<body>Node that contains data and pointers to a parent node, left, middle, and right child.Instance Variables	data	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	Data contained in Node.	parent	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	The parent of Node.	leftChild	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	The left child of Node.	middleChild	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of middleChild	rightChild	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	The right child of Node.</body>
</comment>

<class>
<name>HeapCalculatorInterface</name>
<environment>Smalltalk</environment>
<super>UI.ApplicationModel</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>heapOne heapTwo AddField RemoveField heapOneOutput heapTwoOutput </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category></category>
<attributes>
<package>HeapCalculator</package>
</attributes>
</class>

<comment>
<class-id>HeapCalculatorInterface</class-id>
<body>Interface for the Heap Calculator</body>
</comment>

<methods>
<class-id>HeapCalculatorInterface class</class-id> <category>interface specs</category>

<body package="HeapCalculator" selector="windowSpec">windowSpec	"Tools.UIPainter new openOnClass: self andSelector: #windowSpec"	&lt;resource: #canvas&gt;	^#(#{UI.FullSpec} 		#window: 		#(#{UI.WindowSpec} 			#label: 'Heap Calculator' 			#min: #(#{Core.Point} 700 375 ) 			#max: #(#{Core.Point} 0 0 ) 			#bounds: #(#{Graphics.Rectangle} 333 197 1033 572 ) 			#colors: 			#(#{UI.LookPreferences} 				#setForegroundColor: #(#{Graphics.ColorValue} #black ) 				#setBackgroundColor: #(#{Graphics.ColorValue} 7700 7700 7700 ) 				#setSelectionForegroundColor: #(#{Graphics.ColorValue} #black ) 				#setBorderColor: #(#{Graphics.ColorValue} #lightGray ) ) ) 		#component: 		#(#{UI.SpecCollection} 			#collection: #(				#(#{UI.InputFieldSpec} 					#layout: #(#{Graphics.Rectangle} 40 40 140 62 ) 					#name: #AddField 					#model: #AddField ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 40 16 ) 					#name: #labelModify 					#colors: 					#(#{UI.LookPreferences} 						#setForegroundColor: #(#{Graphics.ColorValue} 3522 3522 3522 ) ) 					#label: 'Modify' ) 				#(#{UI.InputFieldSpec} 					#layout: #(#{Graphics.Rectangle} 40 72 140 94 ) 					#name: #RemoveField 					#model: #RemoveField ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 144 40 240 60 ) 					#name: #AddFieldButton 					#model: #addItem 					#label: 'Add Item' 					#defaultable: true ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 144 72 240 92 ) 					#name: #RemoveFieldButton 					#model: #removeItem 					#label: 'Remove Item' 					#defaultable: true ) 				#(#{UI.TextEditorSpec} 					#layout: #(#{Graphics.Rectangle} 344 40 664 168 ) 					#name: #TextEditor1 					#model: #heapOneOutput 					#tabRequiresControl: true ) 				#(#{UI.TextEditorSpec} 					#layout: #(#{Graphics.Rectangle} 344 232 664 360 ) 					#name: #TextEditor2 					#model: #heapTwoOutput 					#tabRequiresControl: true ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 344 16 ) 					#name: #labelHeapOne 					#colors: 					#(#{UI.LookPreferences} 						#setForegroundColor: #(#{Graphics.ColorValue} 3522 3522 3522 ) ) 					#label: 'Heap One' ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 344 208 ) 					#name: #labelHeapTwo 					#colors: 					#(#{UI.LookPreferences} 						#setForegroundColor: #(#{Graphics.ColorValue} 3522 3522 3522 ) ) 					#label: 'Heap Two' ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 344 176 432 200 ) 					#name: #UnionButton 					#model: #performUnison 					#label: 'Union' 					#defaultable: true ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 456 176 552 200 ) 					#name: #IntersectionButton 					#model: #performIntersection 					#label: 'Intersection' 					#defaultable: true ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 576 176 664 200 ) 					#name: #DifferenceButton 					#model: #performDifference 					#label: 'Difference' 					#defaultable: true ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 40 208 ) 					#name: #labelGeneral 					#colors: 					#(#{UI.LookPreferences} 						#setForegroundColor: #(#{Graphics.ColorValue} 3522 3522 3522 ) ) 					#label: 'General' ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 40 232 112 256 ) 					#name: #SaveButton 					#model: #saveHeap 					#label: 'Save' 					#defaultable: true ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 40 264 112 288 ) 					#name: #ClearButton 					#model: #clearHeap 					#label: 'Clear' 					#defaultable: true ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 40 296 112 320 ) 					#name: #SwitchButton 					#model: #switchHeaps 					#label: 'Switch' 					#defaultable: true ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 144 208 ) 					#name: #labelStructure 					#colors: 					#(#{UI.LookPreferences} 						#setForegroundColor: #(#{Graphics.ColorValue} 3522 3522 3522 ) ) 					#label: 'Structure' ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 144 232 216 256 ) 					#name: #BinaryButton 					#flags: 40 					#model: #setBinaryHeap 					#label: 'Binary' 					#defaultable: true ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 144 264 216 288 ) 					#name: #TertiaryButton 					#flags: 40 					#model: #setTertiaryHeap 					#label: 'Tertiary' 					#defaultable: true ) ) ) )</body>
</methods>


<methods>
<class-id>HeapCalculatorInterface</class-id> <category>aspects</category>

<body package="HeapCalculator" selector="AddField">AddField	"This method was generated by UIDefiner.  Any edits made here	may be lost whenever methods are automatically defined.  The	initialization provided below may have been preempted by an	initialize method."	^AddField isNil		ifTrue:			[AddField := String new asValue]		ifFalse:			[AddField]</body>

<body package="HeapCalculator" selector="heapTwoOutput">heapTwoOutput	"This method was generated by UIDefiner.  Any edits made here	may be lost whenever methods are automatically defined.  The	initialization provided below may have been preempted by an	initialize method."	^heapTwoOutput isNil		ifTrue:			[heapTwoOutput := String new asValue]		ifFalse:			[heapTwoOutput]</body>

<body package="HeapCalculator" selector="RemoveField">RemoveField	"This method was generated by UIDefiner.  Any edits made here	may be lost whenever methods are automatically defined.  The	initialization provided below may have been preempted by an	initialize method."	^RemoveField isNil		ifTrue:			[RemoveField := String new asValue]		ifFalse:			[RemoveField]</body>

<body package="HeapCalculator" selector="heapOneOutput">heapOneOutput	"This method was generated by UIDefiner.  Any edits made here	may be lost whenever methods are automatically defined.  The	initialization provided below may have been preempted by an	initialize method."	^heapOneOutput isNil		ifTrue:			[heapOneOutput := String new asValue]		ifFalse:			[heapOneOutput]</body>
</methods>

<methods>
<class-id>HeapCalculatorInterface</class-id> <category>actions</category>

<body package="HeapCalculator" selector="switchHeaps">switchHeaps	| temp |	temp := heapOne.	heapOne := heapTwo.	heapTwo := temp.	self displayHeaps.	^self</body>

<body package="HeapCalculator" selector="performDifference">performDifference	heapOne := (heapTwo difference:heapOne).	self halt.	self displayHeaps.	^self</body>

<body package="HeapCalculator" selector="performIntersection">performIntersection	heapOne := heapOne intersection:heapTwo.	self halt.	self displayHeaps.	^self</body>

<body package="HeapCalculator" selector="clearHeap">clearHeap	heapOne := Smalltalk.BinaryHeap new initialize.	self displayHeaps.	^self</body>

<body package="HeapCalculator" selector="setTertiaryHeap">setTertiaryHeap	"This stub method was generated by UIDefiner"	^self</body>

<body package="HeapCalculator" selector="saveHeap">saveHeap	"Clear out heap two"	heapTwo := Smalltalk.BinaryHeap new initialize.				heapOne isEmpty		"If heap one has elements, copy it over. Otherwise, leave heap two blank"		ifFalse:[	heapTwo := heapOne copy.].	self displayHeaps.	Transcript cr.	^self</body>

<body package="HeapCalculator" selector="performUnison">performUnison	heapOne := heapOne union:heapTwo.	self displayHeaps.	^self</body>

<body package="HeapCalculator" selector="displayHeaps">displayHeaps	| oStreamOne oStreamTwo oStringOne oStringTwo |	oStreamOne := ReadWriteStream on:String new.	oStreamTwo := ReadWriteStream on:String new.	"Get output stream"	heapOne == nil		ifFalse:[	heapOne display:oStreamOne. heapOne display].	heapTwo == nil		ifFalse:[	heapTwo display:oStreamTwo. heapTwo display.].	oStringOne := String new. oStringOne := oStreamOne collection.	oStringTwo := String new. oStringTwo := oStreamTwo collection.	heapOneOutput value:oStringOne.	heapTwoOutput value:oStringTwo.	^self</body>

<body package="HeapCalculator" selector="addItem">addItem	heapOne == nil		ifTrue:[heapOne := Smalltalk.BinaryHeap new initialize.].	"Prevent blank actions"	AddField value = ''		ifFalse:[ heapOne add: AddField value asNumber. AddField value: ''. self displayHeaps.].	^self</body>

<body package="HeapCalculator" selector="removeItem">removeItem	"Prevent blank actions"	RemoveField value = ''		ifFalse:[heapOne removeElement: RemoveField value asNumber.].	RemoveField value:''.	self displayHeaps.	^self</body>

<body package="HeapCalculator" selector="setBinaryHeap">setBinaryHeap	"This stub method was generated by UIDefiner"	^self</body>
</methods>


<methods>
<class-id>Queue class</class-id> <category>instance creation</category>

<body package="HeapCalculator" selector="new">new	"Answer a newly created and initialized instance."	^super new initialize</body>
</methods>


<methods>
<class-id>Queue</class-id> <category>accessing</category>

<body package="HeapCalculator" selector="root">root	^root</body>

<body package="HeapCalculator" selector="dequeue">dequeue	| item |	self isEmpty		ifTrue:[^nil]		ifFalse:[item := self root data. root hasRightChild ifTrue:[self root: root rightChild] ifFalse:[self root: nil]. count := count - 1.].	^item.</body>

<body package="HeapCalculator" selector="isEmpty">isEmpty	^self root == nil.</body>

<body package="HeapCalculator" selector="count:">count: anObject	count := anObject</body>

<body package="HeapCalculator" selector="numberOfItems">numberOfItems	^count.</body>

<body package="HeapCalculator" selector="count">count	^count</body>

<body package="HeapCalculator" selector="root:">root: anObject	root := anObject</body>

<body package="HeapCalculator" selector="enqueue:">enqueue: item	| current newNode |	current := self root.	newNode := Smalltalk.BinaryNode new initialize.	newNode data: item.	self isEmpty		ifTrue:[self root: newNode. count := count + 1]		ifFalse:[[current hasRightChild] whileTrue: [current := current rightChild.]. current rightChild: newNode. count := count + 1].</body>

<body package="HeapCalculator" selector="display">display	| current |		self isEmpty		ifFalse:[			current := self root.			[current == nil] whileFalse:[				Transcript show:current data printString;show:' '.				current := current rightChild.].].</body>
</methods>

<methods>
<class-id>Queue</class-id> <category>initialize-release</category>

<body package="HeapCalculator" selector="initialize">initialize	"Initialize a newly created instance. This method must answer the receiver."	super initialize.	root := nil.	count := 0.	^self</body>
</methods>


<methods>
<class-id>BinaryHeap class</class-id> <category>instance creation</category>

<body package="HeapCalculator" selector="new">new	"Answer a newly created and initialized instance."	^super new initialize</body>
</methods>


<methods>
<class-id>BinaryHeap</class-id> <category>accessing</category>

<body package="HeapCalculator" selector="find:subtree:">find: aNode subtree: subRoot	| found |	found := false.	subRoot = aNode			ifTrue:[found := true]			ifFalse:[				subRoot hasLeftChild ifTrue:[found := found | (self find:aNode subtree:subRoot leftChild)].				subRoot hasRightChild ifTrue:[found := found | (self find:aNode subtree:subRoot rightChild)].].	^found.</body>

<body package="HeapCalculator" selector="display">display	| aQueue current |	aQueue := Smalltalk.Queue new initialize.	self isEmpty		ifFalse:[			"Add our root to the queue"			aQueue enqueue: self root.			[aQueue numberOfItems &gt; 0] whileTrue: [				"Pop first item, print it out, add its children"				current := aQueue dequeue.				Transcript show:current data printString;show:' '.				current hasLeftChild ifTrue:[aQueue enqueue:current leftChild.].				current hasRightChild ifTrue:[aQueue enqueue:current rightChild.].].].</body>

<body package="HeapCalculator" selector="root">root	^root</body>

<body package="HeapCalculator" selector="isEmpty">isEmpty	^self root == nil</body>

<body package="HeapCalculator" selector="exists:">exists: findData	| current searchNode |	self isEmpty		ifFalse:[			current := self root.			searchNode := Smalltalk.BinaryNode new initialize.			searchNode data: findData.			^(self find:searchNode subtree:current).]		ifTrue:[^false].</body>

<body package="HeapCalculator" selector="last">last	^last</body>

<body package="HeapCalculator" selector="last:">last: anObject	last := anObject</body>

<body package="HeapCalculator" selector="root:">root: anObject	root := anObject</body>

<body package="HeapCalculator" selector="findNodeWithData:">findNodeWithData: item	| searchNode returnNode |	searchNode := Smalltalk.BinaryNode new initialize.	returnNode := Smalltalk.BinaryNode new initialize.		searchNode data:item.	self isEmpty		ifFalse:[returnNode := self findNode:searchNode subtree:self root].	^returnNode</body>

<body package="HeapCalculator" selector="display:">display:oStream	| aQueue current tString |	tString := String new.	aQueue := Smalltalk.Queue new initialize.	self isEmpty		ifFalse:[			"Add our root to the queue"			aQueue enqueue: self root.			[aQueue numberOfItems &gt; 0] whileTrue: [				"Pop first item, print it out, add its children"				current := aQueue dequeue.				"Place value into string and then onto the stream"				tString := current data printString,' '.				oStream nextPutAll:tString.				current hasLeftChild ifTrue:[aQueue enqueue:current leftChild.].				current hasRightChild ifTrue:[aQueue enqueue:current rightChild.].].].</body>

<body package="HeapCalculator" selector="findNode:subtree:">findNode:aNode subtree:subRoot	| searchNode lSearchNode rSearchNode |		subRoot = aNode			ifTrue:[^subRoot.]			ifFalse:[				"Check left branch"				subRoot hasLeftChild ifTrue:[lSearchNode := self findNode:aNode subtree:subRoot leftChild].				"Check right branch"				subRoot hasRightChild ifTrue:[rSearchNode := self findNode:aNode subtree:subRoot rightChild].].	lSearchNode == nil		ifFalse:[searchNode := lSearchNode].	rSearchNode == nil		ifFalse:[searchNode := rSearchNode].		^searchNode</body>
</methods>

<methods>
<class-id>BinaryHeap</class-id> <category>copying</category>

<body package="HeapCalculator" selector="copy">copy	| heapCopy |	heapCopy := Smalltalk.BinaryHeap new initialize.		self copyNode:(self root) into:heapCopy.	^heapCopy</body>

<body package="HeapCalculator" selector="copyNode:into:">copyNode:aNode into:newHeap	"Insert data into new heap"	newHeap add:aNode data.	"Do same for children"	aNode hasLeftChild		ifTrue:[self copyNode:(aNode leftChild) into:newHeap].	aNode hasRightChild		ifTrue:[self copyNode:(aNode rightChild) into:newHeap].</body>
</methods>

<methods>
<class-id>BinaryHeap</class-id> <category>computation</category>

<body package="HeapCalculator" selector="difference:">difference: aHeap	| newHeap |	"Make a copy of ourself"	newHeap := self copy.	"Go through second heap and remove identical objects"	newHeap isEmpty		ifFalse:[newHeap traverse:(newHeap root) andRemoveDuplicatesFrom:aHeap.].	^newHeap</body>

<body package="HeapCalculator" selector="union:">union: aHeap	| newHeap |	newHeap := Smalltalk.BinaryHeap new initialize.	"Add contents of Heap One"	self isEmpty		ifFalse:[self traverse:(self root) andAddAllTo:newHeap.].	"Add contents of Heap Two"	aHeap isEmpty		ifFalse:[self traverse:(aHeap root) andAddAllTo:newHeap.].	^newHeap</body>

<body package="HeapCalculator" selector="traverse:andRemoveDuplicatesFrom:">traverse:subRoot andRemoveDuplicatesFrom:heap	"Check if data is in the other heap"	(heap exists:subRoot data)		ifTrue:[self removeElement:subRoot data.].	"Traverse children"	subRoot hasChildren		ifTrue:[			subRoot hasLeftChild				ifTrue:[self traverse:(subRoot leftChild) andRemoveDuplicatesFrom:heap].			subRoot hasRightChild				ifTrue:[self traverse:(subRoot rightChild) andRemoveDuplicatesFrom:heap].].	self halt.</body>

<body package="HeapCalculator" selector="intersection:">intersection: aHeap	| newHeap |	newHeap := Smalltalk.BinaryHeap new initialize.	"Being traversal of Heap One"	self isEmpty		ifFalse:[self traverse:(aHeap root) andAddDuplicatesTo:newHeap].		^newHeap</body>

<body package="HeapCalculator" selector="traverse:andAddAllTo:">traverse:subRoot andAddAllTo:heap	"Add the data of our root"	heap add:subRoot data.	"Traverse children"	subRoot hasChildren		ifTrue:[			subRoot hasLeftChild				ifTrue:[self traverse:(subRoot leftChild) andAddAllTo:heap].			subRoot hasRightChild				ifTrue:[self traverse:(subRoot rightChild) andAddAllTo:heap].].</body>

<body package="HeapCalculator" selector="traverse:andAddDuplicatesTo:">traverse:subRoot andAddDuplicatesTo:heap	"Add the data of our root"	(self exists:subRoot data)		ifTrue:[heap add:subRoot data.].	"Traverse children"	subRoot hasChildren		ifTrue:[			subRoot hasLeftChild				ifTrue:[self traverse:(subRoot leftChild) andAddDuplicatesTo:heap].			subRoot hasRightChild				ifTrue:[self traverse:(subRoot rightChild) andAddDuplicatesTo:heap].].</body>
</methods>

<methods>
<class-id>BinaryHeap</class-id> <category>initialize-release</category>

<body package="HeapCalculator" selector="initialize">initialize	"Initialize a newly created instance. This method must answer the receiver."	super initialize.	root := nil.	last := nil.		^self</body>
</methods>

<methods>
<class-id>BinaryHeap</class-id> <category>modify</category>

<body package="HeapCalculator" selector="addToNextNode:">addToNextNode: aNode	| current |	current := (self last).	"Move to node parent while node is not a left child or root"	[current isRightChild] whileTrue: [current := current parent.].		"If current is a left child then set to its sibling, otherwise leave it at root"	current isLeftChild ifTrue:  [current hasSibling ifTrue: [current := current parent rightChild] ifFalse: [self last: aNode. current parent rightChild: aNode.^self.].].		"Move down the tree and find the bottom left child"	[current hasLeftChild] whileTrue: [current := current leftChild.].	"Now we have the correct placement, set left child and set last"	current leftChild: aNode.	self last: aNode.	^self.</body>

<body package="HeapCalculator" selector="sort">sort	| current temp |	current := self last.	"Let's start sorting, if the child is greater we move it on up"	[current hasParent] whileTrue:[		current &gt; current parent			ifTrue:[temp := current data. current data: current parent data. current parent data: temp. current := current parent.]			ifFalse:[^self.].]</body>

<body package="HeapCalculator" selector="heapify:">heapify: aNode	| temp current |	current := aNode.	[current hasChildren] whileTrue:[			current hasRightChild				ifTrue:[					current &gt; current rightChild							ifFalse:[							temp := current data.							current data: current rightChild data.							current rightChild data: temp.							current := current rightChild.].].			current hasLeftChild				ifTrue:[					current &gt; current leftChild						ifTrue:[^self.]						ifFalse:[							temp := current data.							current data: current leftChild data.							current leftChild data: temp.							current := current leftChild.].].].	^self.</body>

<body package="HeapCalculator" selector="findNextNode">findNextNode	| current |	self root == nil		ifTrue:[^self]		ifFalse:[			current := self root.			[current hasChildren] whileTrue:[current hasRightChild ifTrue:[current := current rightChild.] ifFalse:[current := current leftChild.].].			self last: current.].</body>

<body package="HeapCalculator" selector="siftDown:">siftDown: aNode	| current temp |	current := aNode.	[current hasChildren] whileTrue: [		current hasRightChild			ifTrue:[temp := current data. current data: current rightChild data. current rightChild data: temp. current := current rightChild]			ifFalse:[temp := current data. current data: current leftChild data. current leftChild data: temp. current := current leftChild].].</body>

<body package="HeapCalculator" selector="removeElement:">removeElement: data	| current |	"Check to make sure item exists in list"	(self exists:data)		ifTrue:[			"If the item exists then we want to grab the node"			current := self findNodeWithData: data.			"Switch the data from last into the node we want to remove"			current data: (self last data).			"Remove the last node from our tree"			self removeLast.			"Now that we have removed last, rebuild current into our heap"			self heapify: current.].</body>

<body package="HeapCalculator" selector="removeLast">removeLast	| current |	current := self last.	current isRoot		"If last is root, delete root"		ifTrue:[self root: nil]		"If last is anything else, move to parent and delete correct child"		ifFalse:[			current isLeftChild				ifTrue:[					current := current parent.					current leftChild: nil.]				ifFalse:[					current := current parent.					current rightChild: nil.].].	"Now we have deleted last, we need to update it's location"	self findNextNode.</body>

<body package="HeapCalculator" selector="add:">add: data		| aNode |	aNode := Smalltalk.BinaryNode new initialize.	aNode data:data.		"Check to make sure item doesn't exist in heap"	(self exists:data)		ifFalse:[			root == nil				"If we have an empty heap, add at root"				ifTrue: [self root: aNode. self last: aNode.]				"Otherwise find next positoin"				ifFalse: [self addToNextNode:aNode. self sort.].].</body>
</methods>

<methods>
<class-id>BinaryHeap</class-id> <category>tracing</category>

<body package="HeapCalculator" selector="findNextSpot">findNextSpot	| nextSpot |	"find next spot"	^nextSpot</body>
</methods>


<methods>
<class-id>TertiaryNode class</class-id> <category>instance creation</category>

<body package="HeapCalculator" selector="new">new	"Answer a newly created and initialized instance."	^super new initialize</body>
</methods>


<methods>
<class-id>TertiaryNode</class-id> <category>accessing</category>

<body package="HeapCalculator" selector="data">data	^data</body>

<body package="HeapCalculator" selector="leftChild">leftChild	^leftChild</body>

<body package="HeapCalculator" selector="rightChild:">rightChild: anObject	rightChild := anObject</body>

<body package="HeapCalculator" selector="data:">data: anObject	data := anObject</body>

<body package="HeapCalculator" selector="rightChild">rightChild	^rightChild</body>

<body package="HeapCalculator" selector="parent">parent	^parent</body>

<body package="HeapCalculator" selector="middleChild:">middleChild: anObject	middleChild := anObject</body>

<body package="HeapCalculator" selector="parent:">parent: anObject	parent := anObject</body>

<body package="HeapCalculator" selector="middleChild">middleChild	^middleChild</body>

<body package="HeapCalculator" selector="leftChild:">leftChild: anObject	leftChild := anObject</body>
</methods>

<methods>
<class-id>TertiaryNode</class-id> <category>initialize-release</category>

<body package="HeapCalculator" selector="initialize">initialize	super initialize.	data := nil.	parent := nil.	leftChild := nil.	middleChild := nil.	rightChild := nil.	^self</body>
</methods>


<methods>
<class-id>BinaryNode class</class-id> <category>instance creation</category>

<body package="HeapCalculator" selector="new">new	"Answer a newly created and initialized instance."	^super new initialize</body>
</methods>


<methods>
<class-id>BinaryNode</class-id> <category>comparing</category>

<body package="HeapCalculator" selector="hasRightChild">hasRightChild	self rightChild == nil		ifTrue:[^false]		ifFalse:[^true]</body>

<body package="HeapCalculator" selector="isLeftChild">isLeftChild	self hasParent		ifTrue:[^(self parent leftChild == self)]		ifFalse:[^false].</body>

<body package="HeapCalculator" selector="isRightChild">isRightChild	self hasParent		ifTrue:[^(self parent rightChild == self)]		ifFalse:[^false].</body>

<body package="HeapCalculator" selector="&gt;">&gt; aNode	^(self data) &gt; (aNode data)</body>

<body package="HeapCalculator" selector="hasSibling">hasSibling	self parent leftChild == self		ifTrue:[self parent rightChild == nil ifTrue:[^false] ifFalse:[^true]]		ifFalse:[self parent leftChild ==nil ifTrue:[^false] ifFalse:[^true]].</body>

<body package="HeapCalculator" selector="isRoot">isRoot	^self parent == nil</body>

<body package="HeapCalculator" selector="=">= aNode	aNode = nil		ifFalse: [^(self data) = (aNode data)]		ifTrue: [^false].</body>

<body package="HeapCalculator" selector="hasParent">hasParent	self parent == nil		ifTrue:[^false]		ifFalse:[^true]</body>

<body package="HeapCalculator" selector="hasChildren">hasChildren	^((self hasLeftChild) | (self hasRightChild))</body>

<body package="HeapCalculator" selector="hasLeftChild">hasLeftChild	self leftChild == nil		ifTrue:[^false]		ifFalse:[^true]</body>

<body package="HeapCalculator" selector="&lt;">&lt; aNode	^(self data) &lt; (aNode data)</body>
</methods>

<methods>
<class-id>BinaryNode</class-id> <category>accessing</category>

<body package="HeapCalculator" selector="data:">data: anObject	data := anObject</body>

<body package="HeapCalculator" selector="rightChild">rightChild	^rightChild</body>

<body package="HeapCalculator" selector="parent">parent	^parent</body>

<body package="HeapCalculator" selector="parent:">parent: anObject	parent := anObject</body>

<body package="HeapCalculator" selector="leftChild:">leftChild: anObject	leftChild := anObject.	anObject == nil		ifFalse:[anObject parent: self.].</body>

<body package="HeapCalculator" selector="data">data	^data</body>

<body package="HeapCalculator" selector="leftChild">leftChild	^leftChild</body>

<body package="HeapCalculator" selector="rightChild:">rightChild: anObject	rightChild := anObject.	anObject == nil		ifFalse:[anObject parent: self.].</body>
</methods>

<methods>
<class-id>BinaryNode</class-id> <category>initialize-release</category>

<body package="HeapCalculator" selector="initialize">initialize	super initialize.	data := nil.	leftChild := nil.	rightChild := nil.	parent := nil.	^self</body>
</methods>



</st-source>
