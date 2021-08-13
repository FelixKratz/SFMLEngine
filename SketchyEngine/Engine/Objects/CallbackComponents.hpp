//
//  CallbackTarget.hpp
//  StrategyGame
//
//  Created by Felix Kratz on 05.09.20.
//  Copyright © 2020 fk. All rights reserved.
//

#pragma once
class Clickable;
class CallbackTarget;

template <class CallbackArg, class CallbackType>
using callbackType = void (CallbackType::*)(CallbackArg* _sender);

template <class SourceType, class TargetType, class CallbackArg>
callbackType<CallbackArg, TargetType> transformAnyCallback(void (SourceType::*callback)(CallbackArg* _callbackArg)) {
    return (callbackType<CallbackArg, TargetType>)callback;
}

template <class Type, class CallbackArg>
callbackType<Clickable, CallbackTarget> transformCallback(void (Type::*callback)(CallbackArg* _callbackArg)) {
    return (callbackType<Clickable, CallbackTarget>)callback;
}

class CallbackTarget {
public:
    void *keyBoardFocus{ nullptr };
};

class CallbackSender {
protected:
    CallbackTarget* _target = nullptr;
public:
    void setCallbackTarget(CallbackTarget* target) { _target = target; };
    CallbackTarget* getCallbackTarget() { return _target; };
};

