#include "PapyrusArgs.h"
#include "PapyrusNativeFunctions.h"

//// type -> VMValue

template <> void PackValue <void>(VMValue * dst, void * src)
{
	dst->SetNone();
}

template <> void PackValue <UInt32>(VMValue * dst, UInt32 * src)
{
	dst->SetInt(*src);
}

template <> void PackValue <SInt32>(VMValue * dst, SInt32 * src)
{
	dst->SetInt(*src);
}

template <> void PackValue <float>(VMValue * dst, float * src)
{
	dst->SetFloat(*src);
}

template <> void PackValue <bool>(VMValue * dst, bool * src)
{
	dst->SetBool(*src);
}

//// VMValue -> type

template <> void UnpackValue <StaticFunctionTag *>(StaticFunctionTag ** dst, VMValue * src, PapyrusClassRegistry * registry)
{
	*dst = NULL;
}

template <> void UnpackValue <float>(float * dst, VMValue * src, PapyrusClassRegistry * registry)
{
	switch(src->type)
	{
		case VMValue::kType_Int:
			*dst = src->data.i;
			break;

		case VMValue::kType_Float:
			*dst = src->data.f;
			break;

		case VMValue::kType_Bool:
			*dst = src->data.b;
			break;

		default:
			*dst = 0;
			break;
	}
}

template <> void UnpackValue <UInt32>(UInt32 * dst, VMValue * src, PapyrusClassRegistry * registry)
{
	switch(src->type)
	{
	case VMValue::kType_Int:
		*dst = src->data.u;
		break;

	case VMValue::kType_Float:
		*dst = src->data.f;
		break;

	case VMValue::kType_Bool:
		*dst = src->data.b;
		break;

	default:
		*dst = 0;
		break;
	}
}

template <> void UnpackValue <SInt32>(SInt32 * dst, VMValue * src, PapyrusClassRegistry * registry)
{
	switch(src->type)
	{
	case VMValue::kType_Int:
		*dst = src->data.u;
		break;

	case VMValue::kType_Float:
		*dst = src->data.f;
		break;

	case VMValue::kType_Bool:
		*dst = src->data.b;
		break;

	default:
		*dst = 0;
		break;
	}
}

template <> void UnpackValue <bool>(bool * dst, VMValue * src, PapyrusClassRegistry * registry)
{
	switch(src->type)
	{
	case VMValue::kType_Int:
		*dst = src->data.u != 0;
		break;

	case VMValue::kType_Float:
		*dst = src->data.f != 0;
		break;

	case VMValue::kType_Bool:
		*dst = src->data.b;
		break;

	default:
		*dst = 0;
		break;
	}
}
