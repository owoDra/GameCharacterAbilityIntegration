// Copyright (C) 2023 owoDra

#pragma once

#include "Logging/LogMacros.h"

GCAINTG_API DECLARE_LOG_CATEGORY_EXTERN(LogGCAI, Log, All);

#if !UE_BUILD_SHIPPING

#define GCAILOG(FormattedText, ...) UE_LOG(LogGCAI, Log, FormattedText, __VA_ARGS__)

#define GCAIENSURE(InExpression) ensure(InExpression)
#define GCAIENSURE_MSG(InExpression, InFormat, ...) ensureMsgf(InExpression, InFormat, __VA_ARGS__)
#define GCAIENSURE_ALWAYS_MSG(InExpression, InFormat, ...) ensureAlwaysMsgf(InExpression, InFormat, __VA_ARGS__)

#define GCAICHECK(InExpression) check(InExpression)
#define GCAICHECK_MSG(InExpression, InFormat, ...) checkf(InExpression, InFormat, __VA_ARGS__)

#else

#define GCAILOG(FormattedText, ...)

#define GCAIENSURE(InExpression) InExpression
#define GCAIENSURE_MSG(InExpression, InFormat, ...) InExpression
#define GCAIENSURE_ALWAYS_MSG(InExpression, InFormat, ...) InExpression

#define GCAICHECK(InExpression) InExpression
#define GCAICHECK_MSG(InExpression, InFormat, ...) InExpression

#endif