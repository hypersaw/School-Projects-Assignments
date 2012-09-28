<?xml version="1.0"?>

<st-source>
<time-stamp>From VisualWorks® Personal Use Edition, 7.9 of May 11, 2012 on September 28, 2012 at 5:45:21 PM</time-stamp>


<component-created>
<name>BinarySearchTree</name> <type>package</type>
</component-created><!-- Package BinarySearchTree* -->


<component-property>
<name>BinarySearchTree</name> <type>package</type>
<property>packageName</property> <value>'BinarySearchTree'</value>
</component-property>

<component-property>
<name>BinarySearchTree</name> <type>package</type>
<property>comment</property> <value>'Binary Tree package. Contains a Binary Tree class, a Node class, and a "Weighted" Character class. Also including is a GUI that acts as the View and Controller.'</value>
</component-property>

<class>
<name>WeightedCharacter</name>
<environment>Smalltalk</environment>
<super>Core.Object</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>value weight </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category>BinarySearchTree</category>
<attributes>
<package>BinarySearchTree</package>
</attributes>
</class>

<comment>
<class-id>WeightedCharacter</class-id>
<body>WeightedCharacter holds a value and a weight.Instance Variables	value	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of value	weight	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of weight</body>
</comment>

<class>
<name>Node</name>
<environment>Smalltalk</environment>
<super>Core.Object</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>data leftChild rightChild </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category>BinarySearchTree</category>
<attributes>
<package>BinarySearchTree</package>
</attributes>
</class>

<comment>
<class-id>Node</class-id>
<body>Node holds data and a left and right child.Instance Variables	data	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of data	leftChild	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of leftChild	rightChild	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of rightChild</body>
</comment>

<class>
<name>BSTInterface</name>
<environment>Smalltalk</environment>
<super>UI.ApplicationModel</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>userInput ouputString charTree stringInput outputField </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category></category>
<attributes>
<package>BinarySearchTree</package>
</attributes>
</class>

<comment>
<class-id>BSTInterface</class-id>
<body>BSTInterface has not been commented.  The comment should state the purpose of the class and also explain any unobvious aspects of the implementation. Instance Variables	inputString	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of inputString	ouputString	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of ouputString</body>
</comment>

<class>
<name>BinarySearchTree</name>
<environment>Smalltalk</environment>
<super>Core.Object</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>root </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category>BinarySearchTree</category>
<attributes>
<package>BinarySearchTree</package>
</attributes>
</class>

<comment>
<class-id>BinarySearchTree</class-id>
<body>BinarySearchTree stores data in a binary tree.Instance Variables	root	&lt;MessageForwarder | Object | ProtoObject | ProtoObject&gt;	description of root</body>
</comment>

<methods>
<class-id>WeightedCharacter class</class-id> <category>instance creation</category>

<body package="BinarySearchTree" selector="new">new	"Answer a newly created and initialized instance."	^super new initialize</body>
</methods>


<methods>
<class-id>WeightedCharacter</class-id> <category>comparing</category>

<body package="BinarySearchTree" selector="&gt;">&gt; aWC	^(self value) &gt; (aWC value)</body>

<body package="BinarySearchTree" selector="&lt;">&lt; aWC	^(self value) &lt; (aWC value)</body>

<body package="BinarySearchTree" selector="=">= aWC	^(self value) = (aWC value)</body>
</methods>

<methods>
<class-id>WeightedCharacter</class-id> <category>accessing</category>

<body package="BinarySearchTree" selector="value:">value: anObject	value := anObject</body>

<body package="BinarySearchTree" selector="weight">weight	^ weight</body>

<body package="BinarySearchTree" selector="value">value	^ value</body>

<body package="BinarySearchTree" selector="weight:">weight: anObject	weight := anObject</body>
</methods>

<methods>
<class-id>WeightedCharacter</class-id> <category>testing</category>

<body package="BinarySearchTree" selector="testWC">testWC	WeightedCharacter new initialize value:'a'.</body>
</methods>

<methods>
<class-id>WeightedCharacter</class-id> <category>initialize-release</category>

<body package="BinarySearchTree" selector="initialize">initialize	"Initialize a newly created instance. This method must answer the receiver."	super initialize.	" *** Edit the following to properly initialize instance variables ***"	value := nil.	weight := 0.	" *** And replace this comment with additional initialization code *** "	^self</body>
</methods>


<methods>
<class-id>BinarySearchTree class</class-id> <category>instance creation</category>

<body package="BinarySearchTree" selector="new">new	"Answer a newly created and initialized instance."	^super new initialize</body>
</methods>


<methods>
<class-id>BinarySearchTree</class-id> <category>modify</category>

<body package="BinarySearchTree" selector="add:">add: data	| aNode |	aNode := Smalltalk.Node new initialize.	aNode data:data.	root == nil		ifTrue: [self root: aNode. root data weight: root data weight + 1]		ifFalse: [			root = aNode				ifTrue: [root data weight: root data weight + 1]				ifFalse: [self rootNode:root newNode:aNode]]</body>

<body package="BinarySearchTree" selector="rootNode:newNode:">rootNode:subTreeRoot newNode:aNode	subTreeRoot = aNode		ifTrue: [subTreeRoot data weight: subTreeRoot data weight + 1].	subTreeRoot &gt; aNode		ifTrue: [			subTreeRoot leftChild == nil				ifTrue: [subTreeRoot leftChild:aNode. subTreeRoot leftChild data weight: subTreeRoot leftChild data weight + 1.]				ifFalse: [self rootNode:(subTreeRoot leftChild) newNode:aNode]]		ifFalse: [			subTreeRoot rightChild == nil				ifTrue: [subTreeRoot rightChild:aNode. subTreeRoot rightChild data weight: subTreeRoot rightChild data weight + 1.]				ifFalse: [self rootNode:(subTreeRoot rightChild) newNode:aNode]]</body>
</methods>

<methods>
<class-id>BinarySearchTree</class-id> <category>accessing</category>

<body package="BinarySearchTree" selector="subTreeInOrder:withOutput:">subTreeInOrder:subTreeRoot withOutput:oStream	| tString |	tString := String new.		(subTreeRoot leftChild) == nil		ifFalse: [self subTreeInOrder:(subTreeRoot leftChild) withOutput:oStream].		tString := '(',(subTreeRoot data value asSymbol),', ',(subTreeRoot data weight printString),') '.	oStream nextPutAll:tString.		(subTreeRoot rightChild) == nil		ifFalse: [self subTreeInOrder:(subTreeRoot rightChild) withOutput:oStream].</body>

<body package="BinarySearchTree" selector="subTreePreOrder:">subTreePreOrder: subTreeRoot	Transcript show: subTreeRoot data value.	(subTreeRoot leftChild) == nil		ifFalse: [self subTreePreOrder: (subTreeRoot leftChild)].	(subTreeRoot rightChild) == nil		ifFalse: [self subTreePreOrder: (subTreeRoot rightChild)].</body>

<body package="BinarySearchTree" selector="subTreePreOrder:withOutput:">subTreePreOrder:subTreeRoot withOutput:oStream	| tString |	tString := String new.	tString := '(',(subTreeRoot data value asSymbol),', ',(subTreeRoot data weight printString),') '.	oStream nextPutAll:tString.	(subTreeRoot leftChild) == nil		ifFalse: [self subTreePreOrder:(subTreeRoot leftChild) withOutput:oStream].	(subTreeRoot rightChild) == nil		ifFalse: [self subTreePreOrder:(subTreeRoot rightChild) withOutput:oStream].</body>

<body package="BinarySearchTree" selector="displayMode:">displayMode:value	value = 1		ifTrue: [Transcript show: 'Preorder: '. self subTreePreOrder: root. Transcript show: '';cr.]		ifFalse: [Transcript show: 'Inorder: '. self subTreeInOrder: root. Transcript show: '';cr.]</body>

<body package="BinarySearchTree" selector="root:">root: anObject	root := anObject</body>

<body package="BinarySearchTree" selector="subTreeInOrder:">subTreeInOrder: subTreeRoot	(subTreeRoot leftChild) == nil		ifFalse: [self subTreeInOrder:(subTreeRoot leftChild)].	Transcript show: subTreeRoot data value.	(subTreeRoot rightChild) == nil		ifFalse: [self subTreeInOrder:(subTreeRoot rightChild)].</body>

<body package="BinarySearchTree" selector="displayMode:withOutput:">displayMode:value withOutput:oStream	value = 1		ifTrue: [self subTreePreOrder:root withOutput:oStream.]		ifFalse: [self subTreeInOrder:root withOutput:oStream.]</body>

<body package="BinarySearchTree" selector="root">root	^ root</body>
</methods>

<methods>
<class-id>BinarySearchTree</class-id> <category>testing</category>

<body package="BinarySearchTree" selector="startTest">startTest	| tree |	"Initiate Tree"	tree := BinarySearchTree new initialize.	"Populate Tree"	tree add: (Smalltalk.Node new initialize data: 't').	tree add: (Smalltalk.Node new initialize data: 'h').	tree add: (Smalltalk.Node new initialize data: 'i').	tree add: (Smalltalk.Node new initialize data: 's').	tree add: (Smalltalk.Node new initialize data: 'a').	tree add: (Smalltalk.Node new initialize data: 'r').	tree add: (Smalltalk.Node new initialize data: 'n').	tree add: (Smalltalk.Node new initialize data: 'g').	"Test display modes"	tree displayMode: 1.	tree displayMode: 2.	"Display expected outputs"	Transcript show: 'Correct answers'; cr.	Transcript show: 'Preoder: t h a g i s r n'; cr.	Transcript show: 'Inorder: a g h i n r s t'; cr.</body>
</methods>

<methods>
<class-id>BinarySearchTree</class-id> <category>initialize-release</category>

<body package="BinarySearchTree" selector="initialize">initialize	super initialize.	root := nil.	^self</body>
</methods>


<methods>
<class-id>BSTInterface class</class-id> <category>interface specs</category>

<body package="BinarySearchTree" selector="windowSpec">windowSpec	"Tools.UIPainter new openOnClass: self andSelector: #windowSpec"	&lt;resource: #canvas&gt;	^#(#{UI.FullSpec} 		#window: 		#(#{UI.WindowSpec} 			#label: 'BST Interface' 			#min: #(#{Core.Point} 500 300 ) 			#max: #(#{Core.Point} 500 300 ) 			#bounds: #(#{Graphics.Rectangle} 433 234 933 534 ) 			#colors: 			#(#{UI.LookPreferences} 				#setForegroundColor: #(#{Graphics.ColorValue} 3522 3522 3522 ) 				#setBackgroundColor: #(#{Graphics.ColorValue} 5734 5734 5734 ) 				#setSelectionForegroundColor: #(#{Graphics.ColorValue} #black ) 				#setSelectionBackgroundColor: #(#{Graphics.ColorValue} 5734 5734 5734 ) 				#setBorderColor: #(#{Graphics.ColorValue} #lightGray ) ) ) 		#component: 		#(#{UI.SpecCollection} 			#collection: #(				#(#{UI.InputFieldSpec} 					#layout: #(#{Graphics.Rectangle} 88 16 376 56 ) 					#name: #stringInput 					#colors: 					#(#{UI.LookPreferences} 						#setForegroundColor: #(#{Graphics.ColorValue} 3522 3522 3522 ) 						#setBackgroundColor: #(#{Graphics.ColorValue} 7044 7044 7044 ) 						#setSelectionForegroundColor: #(#{Graphics.ColorValue} #black ) 						#setSelectionBackgroundColor: #(#{Graphics.ColorValue} 5734 5734 5734 ) 						#setBorderColor: #(#{Graphics.ColorValue} #lightGray ) ) 					#model: #stringInput 					#type: #string ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 8 24 ) 					#name: #UILabel 					#colors: 					#(#{UI.LookPreferences} 						#setForegroundColor: #(#{Graphics.ColorValue} #black ) 						#setBackgroundColor: #(#{Graphics.ColorValue} #black ) ) 					#label: 'User Input' 					#style: #pixelFixed ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 37 72 ) 					#name: #OutputLabel 					#colors: 					#(#{UI.LookPreferences} 						#setForegroundColor: #(#{Graphics.ColorValue} #black ) 						#setBackgroundColor: #(#{Graphics.ColorValue} #black ) ) 					#label: 'Output' 					#style: #pixelFixed ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 408 16 480 40 ) 					#name: #GenerateButton 					#model: #clickGenerate 					#label: 'Generate' 					#isDefault: false 					#defaultable: true ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 408 48 480 64 ) 					#name: #preorderButton 					#flags: 40 					#model: #clickPreorder 					#label: 'Preorder' 					#defaultable: true ) 				#(#{UI.ActionButtonSpec} 					#layout: #(#{Graphics.Rectangle} 408 72 480 96 ) 					#name: #inorderButton 					#flags: 40 					#model: #clickInorder 					#label: 'Inorder' 					#defaultable: true ) 				#(#{UI.TextEditorSpec} 					#layout: #(#{Graphics.Rectangle} 88 72 376 176 ) 					#name: #outputField 					#colors: 					#(#{UI.LookPreferences} 						#setForegroundColor: #(#{Graphics.ColorValue} #black ) 						#setBackgroundColor: #(#{Graphics.ColorValue} 7044 7044 7044 ) 						#setSelectionForegroundColor: #(#{Graphics.ColorValue} #black ) 						#setSelectionBackgroundColor: #(#{Graphics.ColorValue} 5734 5734 5734 ) ) 					#model: #outputField 					#tabRequiresControl: true ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 40 200 ) 					#name: #Label1 					#label: 'Type in a string of words (seperated by white space) into the User Input field.' ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 40 224 ) 					#name: #Label2 					#label: 'When you are done, click "Generate" to generate a Binary Tree containing the' ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 40 248 ) 					#name: #Label3 					#label: 'characters from the User Input field. Click "Preorder" to display the tree in preorder,' ) 				#(#{UI.LabelSpec} 					#layout: #(#{Core.Point} 40 272 ) 					#name: #Label4 					#label: 'and click "Inorder" to display the tree in in-order.' ) ) ) )</body>
</methods>


<methods>
<class-id>BSTInterface</class-id> <category>actions</category>

<body package="BinarySearchTree" selector="clickGenerate">clickGenerate	| inputString |	"Initiate tree"	charTree := BinarySearchTree new initialize.	"Pull string from field"	inputString := stringInput value.	Transcript show: 'User input: ', inputString printString; cr.	inputString := inputString readStream.	"Parse our string"	[inputString atEnd] whileFalse: [		(inputString upTo: $ ) do: [			:letter |			(',./;[]\!@#w$%^&amp;*()_+-=&lt;&gt;?:{}|`~' findString:letter asSymbol startingAt:1) = 0				ifTrue: [charTree add: (WeightedCharacter new initialize value: letter)].].].	(self builder componentAt: #preorderButton) enable.	(self builder componentAt: #inorderButton) enable.</body>

<body package="BinarySearchTree" selector="clickInorder">clickInorder	| oStream oString |	outputField value:'Processing...'.	oStream := ReadWriteStream on:String new.	charTree displayMode:2 withOutput:oStream.	oString := String new. oString := oStream collection.	outputField value:oString.</body>

<body package="BinarySearchTree" selector="clickPreorder">clickPreorder	| oStream oString |	outputField value:'Processing...'.	oStream := ReadWriteStream on:String new.	charTree displayMode:1 withOutput:oStream.	oString := String new. oString := oStream collection.	outputField value:oString.</body>
</methods>

<methods>
<class-id>BSTInterface</class-id> <category>aspects</category>

<body package="BinarySearchTree" selector="outputField">outputField	"This method was generated by UIDefiner.  Any edits made here	may be lost whenever methods are automatically defined.  The	initialization provided below may have been preempted by an	initialize method."	^outputField isNil		ifTrue:			[outputField := String new asValue]		ifFalse:			[outputField]</body>

<body package="BinarySearchTree" selector="stringInput">stringInput	"This method was generated by UIDefiner.  Any edits made here	may be lost whenever methods are automatically defined.  The	initialization provided below may have been preempted by an	initialize method."	^stringInput isNil		ifTrue:			[stringInput := String new asValue]		ifFalse:			[stringInput]</body>
</methods>


<methods>
<class-id>Node class</class-id> <category>instance creation</category>

<body package="BinarySearchTree" selector="new">new	"Answer a newly created and initialized instance."	^super new initialize</body>
</methods>


<methods>
<class-id>Node</class-id> <category>comparing</category>

<body package="BinarySearchTree" selector="&gt;">&gt; aNode	^(self data) &gt; (aNode data)</body>

<body package="BinarySearchTree" selector="&lt;">&lt; aNode	^(self data) &lt; (aNode data)</body>

<body package="BinarySearchTree" selector="=">= aNode	^(self data) = (aNode data)</body>
</methods>

<methods>
<class-id>Node</class-id> <category>accessing</category>

<body package="BinarySearchTree" selector="rightChild:">rightChild: anObject	rightChild := anObject</body>

<body package="BinarySearchTree" selector="data:">data: anObject	data := anObject</body>

<body package="BinarySearchTree" selector="rightChild">rightChild	^ rightChild</body>

<body package="BinarySearchTree" selector="leftChild:">leftChild: anObject	leftChild := anObject</body>

<body package="BinarySearchTree" selector="data">data	^ data</body>

<body package="BinarySearchTree" selector="leftChild">leftChild	^ leftChild</body>
</methods>

<methods>
<class-id>Node</class-id> <category>initialize-release</category>

<body package="BinarySearchTree" selector="initialize">initialize	super initialize.		data := nil.	leftChild := nil.	rightChild := nil.		^self</body>
</methods>



</st-source>
