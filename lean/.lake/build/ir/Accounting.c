// Lean compiler output
// Module: Accounting
// Imports: public import Init public meta import Init
#include <lean/lean.h>
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-label"
#elif defined(__GNUC__) && !defined(__CLANG__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
#ifdef __cplusplus
extern "C" {
#endif
lean_object* lean_nat_to_int(lean_object*);
lean_object* l_List_reverse___redArg(lean_object*);
lean_object* lean_int_neg(lean_object*);
lean_object* l_List_foldr___at___00Lean_Omega_IntList_sum_spec__0(lean_object*, lean_object*);
lean_object* lean_int_ediv(lean_object*, lean_object*);
lean_object* lean_int_add(lean_object*, lean_object*);
lean_object* lean_array_mk(lean_object*);
lean_object* lean_array_get_size(lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
size_t lean_usize_of_nat(lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
size_t lean_usize_sub(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* l_Int_sign(lean_object*);
lean_object* lean_nat_abs(lean_object*);
lean_object* lean_int_mul(lean_object*, lean_object*);
uint8_t lean_int_dec_le(lean_object*, lean_object*);
lean_object* lean_int_sub(lean_object*, lean_object*);
lean_object* l_List_mapTR_loop___at___00Lean_Omega_IntList_neg_spec__0(lean_object*, lean_object*);
static lean_once_cell_t lp_accounting_List_sum___at___00postingSum_spec__0___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_accounting_List_sum___at___00postingSum_spec__0___closed__0;
LEAN_EXPORT lean_object* lp_accounting_List_sum___at___00postingSum_spec__0(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_sum___at___00postingSum_spec__0___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_postingSum(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_postingSum___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_reversePosting(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_reversePosting___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_reverseAll(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00amounts_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_amounts(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_reverseEntry(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00reverseEntries_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_reverseEntries(lean_object*);
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOf_spec__0_spec__0(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOf_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00balanceOf_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00balanceOf_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_balanceOf(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_balanceOf___boxed(lean_object*, lean_object*);
static lean_once_cell_t lp_accounting_roundHalfUp___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_accounting_roundHalfUp___closed__0;
LEAN_EXPORT lean_object* lp_accounting_roundHalfUp(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_roundHalfUp___boxed(lean_object*, lean_object*);
static lean_once_cell_t lp_accounting_splitVatInclusive___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_accounting_splitVatInclusive___closed__0;
LEAN_EXPORT lean_object* lp_accounting_splitVatInclusive(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00amountsIn_spec__0_spec__0(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00amountsIn_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00amountsIn_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00amountsIn_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_amountsIn(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_amountsIn___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOfIn_spec__0_spec__0(lean_object*, lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOfIn_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00balanceOfIn_spec__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00balanceOfIn_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_balanceOfIn(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_balanceOfIn___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_reverseCPosting(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00reverseCEntries_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_reverseCEntries(lean_object*);
LEAN_EXPORT lean_object* lp_accounting_conversionEntrySource(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_conversionEntryTarget(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_restate(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_restate___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00perLine_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00perLine_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_perLine(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_perLine___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_perDoc(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_perDoc___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_scaledErr(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_scaledErr___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_applyGuarded(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_applyGuarded___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_foldl___at___00runGuarded_spec__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_List_foldl___at___00runGuarded_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_runGuarded(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_accounting_runGuarded___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static lean_object* _init_lp_accounting_List_sum___at___00postingSum_spec__0___closed__0(void){
_start:
{
lean_object* v___x_1_; lean_object* v___x_2_; 
v___x_1_ = lean_unsigned_to_nat(0u);
v___x_2_ = lean_nat_to_int(v___x_1_);
return v___x_2_;
}
}
LEAN_EXPORT lean_object* lp_accounting_List_sum___at___00postingSum_spec__0(lean_object* v_l_3_){
_start:
{
lean_object* v___x_4_; lean_object* v___x_5_; 
v___x_4_ = lean_obj_once(&lp_accounting_List_sum___at___00postingSum_spec__0___closed__0, &lp_accounting_List_sum___at___00postingSum_spec__0___closed__0_once, _init_lp_accounting_List_sum___at___00postingSum_spec__0___closed__0);
v___x_5_ = l_List_foldr___at___00Lean_Omega_IntList_sum_spec__0(v___x_4_, v_l_3_);
return v___x_5_;
}
}
LEAN_EXPORT lean_object* lp_accounting_List_sum___at___00postingSum_spec__0___boxed(lean_object* v_l_6_){
_start:
{
lean_object* v_res_7_; 
v_res_7_ = lp_accounting_List_sum___at___00postingSum_spec__0(v_l_6_);
lean_dec(v_l_6_);
return v_res_7_;
}
}
LEAN_EXPORT lean_object* lp_accounting_postingSum(lean_object* v_ps_8_){
_start:
{
lean_object* v___x_9_; 
v___x_9_ = lp_accounting_List_sum___at___00postingSum_spec__0(v_ps_8_);
return v___x_9_;
}
}
LEAN_EXPORT lean_object* lp_accounting_postingSum___boxed(lean_object* v_ps_10_){
_start:
{
lean_object* v_res_11_; 
v_res_11_ = lp_accounting_postingSum(v_ps_10_);
lean_dec(v_ps_10_);
return v_res_11_;
}
}
LEAN_EXPORT lean_object* lp_accounting_reversePosting(lean_object* v_a_12_){
_start:
{
lean_object* v___x_13_; 
v___x_13_ = lean_int_neg(v_a_12_);
return v___x_13_;
}
}
LEAN_EXPORT lean_object* lp_accounting_reversePosting___boxed(lean_object* v_a_14_){
_start:
{
lean_object* v_res_15_; 
v_res_15_ = lp_accounting_reversePosting(v_a_14_);
lean_dec(v_a_14_);
return v_res_15_;
}
}
LEAN_EXPORT lean_object* lp_accounting_reverseAll(lean_object* v_ps_16_){
_start:
{
lean_object* v___x_17_; lean_object* v___x_18_; 
v___x_17_ = lean_box(0);
v___x_18_ = l_List_mapTR_loop___at___00Lean_Omega_IntList_neg_spec__0(v_ps_16_, v___x_17_);
return v___x_18_;
}
}
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00amounts_spec__0(lean_object* v_a_19_, lean_object* v_a_20_){
_start:
{
if (lean_obj_tag(v_a_19_) == 0)
{
lean_object* v___x_21_; 
v___x_21_ = l_List_reverse___redArg(v_a_20_);
return v___x_21_;
}
else
{
lean_object* v_head_22_; lean_object* v_tail_23_; lean_object* v___x_25_; uint8_t v_isShared_26_; uint8_t v_isSharedCheck_32_; 
v_head_22_ = lean_ctor_get(v_a_19_, 0);
v_tail_23_ = lean_ctor_get(v_a_19_, 1);
v_isSharedCheck_32_ = !lean_is_exclusive(v_a_19_);
if (v_isSharedCheck_32_ == 0)
{
v___x_25_ = v_a_19_;
v_isShared_26_ = v_isSharedCheck_32_;
goto v_resetjp_24_;
}
else
{
lean_inc(v_tail_23_);
lean_inc(v_head_22_);
lean_dec(v_a_19_);
v___x_25_ = lean_box(0);
v_isShared_26_ = v_isSharedCheck_32_;
goto v_resetjp_24_;
}
v_resetjp_24_:
{
lean_object* v_amount_27_; lean_object* v___x_29_; 
v_amount_27_ = lean_ctor_get(v_head_22_, 1);
lean_inc(v_amount_27_);
lean_dec(v_head_22_);
if (v_isShared_26_ == 0)
{
lean_ctor_set(v___x_25_, 1, v_a_20_);
lean_ctor_set(v___x_25_, 0, v_amount_27_);
v___x_29_ = v___x_25_;
goto v_reusejp_28_;
}
else
{
lean_object* v_reuseFailAlloc_31_; 
v_reuseFailAlloc_31_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_31_, 0, v_amount_27_);
lean_ctor_set(v_reuseFailAlloc_31_, 1, v_a_20_);
v___x_29_ = v_reuseFailAlloc_31_;
goto v_reusejp_28_;
}
v_reusejp_28_:
{
v_a_19_ = v_tail_23_;
v_a_20_ = v___x_29_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_accounting_amounts(lean_object* v_ps_33_){
_start:
{
lean_object* v___x_34_; lean_object* v___x_35_; 
v___x_34_ = lean_box(0);
v___x_35_ = lp_accounting_List_mapTR_loop___at___00amounts_spec__0(v_ps_33_, v___x_34_);
return v___x_35_;
}
}
LEAN_EXPORT lean_object* lp_accounting_reverseEntry(lean_object* v_p_36_){
_start:
{
lean_object* v_account_37_; lean_object* v_amount_38_; lean_object* v___x_40_; uint8_t v_isShared_41_; uint8_t v_isSharedCheck_46_; 
v_account_37_ = lean_ctor_get(v_p_36_, 0);
v_amount_38_ = lean_ctor_get(v_p_36_, 1);
v_isSharedCheck_46_ = !lean_is_exclusive(v_p_36_);
if (v_isSharedCheck_46_ == 0)
{
v___x_40_ = v_p_36_;
v_isShared_41_ = v_isSharedCheck_46_;
goto v_resetjp_39_;
}
else
{
lean_inc(v_amount_38_);
lean_inc(v_account_37_);
lean_dec(v_p_36_);
v___x_40_ = lean_box(0);
v_isShared_41_ = v_isSharedCheck_46_;
goto v_resetjp_39_;
}
v_resetjp_39_:
{
lean_object* v___x_42_; lean_object* v___x_44_; 
v___x_42_ = lean_int_neg(v_amount_38_);
lean_dec(v_amount_38_);
if (v_isShared_41_ == 0)
{
lean_ctor_set(v___x_40_, 1, v___x_42_);
v___x_44_ = v___x_40_;
goto v_reusejp_43_;
}
else
{
lean_object* v_reuseFailAlloc_45_; 
v_reuseFailAlloc_45_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_45_, 0, v_account_37_);
lean_ctor_set(v_reuseFailAlloc_45_, 1, v___x_42_);
v___x_44_ = v_reuseFailAlloc_45_;
goto v_reusejp_43_;
}
v_reusejp_43_:
{
return v___x_44_;
}
}
}
}
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00reverseEntries_spec__0(lean_object* v_a_47_, lean_object* v_a_48_){
_start:
{
if (lean_obj_tag(v_a_47_) == 0)
{
lean_object* v___x_49_; 
v___x_49_ = l_List_reverse___redArg(v_a_48_);
return v___x_49_;
}
else
{
lean_object* v_head_50_; lean_object* v_tail_51_; lean_object* v___x_53_; uint8_t v_isShared_54_; uint8_t v_isSharedCheck_60_; 
v_head_50_ = lean_ctor_get(v_a_47_, 0);
v_tail_51_ = lean_ctor_get(v_a_47_, 1);
v_isSharedCheck_60_ = !lean_is_exclusive(v_a_47_);
if (v_isSharedCheck_60_ == 0)
{
v___x_53_ = v_a_47_;
v_isShared_54_ = v_isSharedCheck_60_;
goto v_resetjp_52_;
}
else
{
lean_inc(v_tail_51_);
lean_inc(v_head_50_);
lean_dec(v_a_47_);
v___x_53_ = lean_box(0);
v_isShared_54_ = v_isSharedCheck_60_;
goto v_resetjp_52_;
}
v_resetjp_52_:
{
lean_object* v___x_55_; lean_object* v___x_57_; 
v___x_55_ = lp_accounting_reverseEntry(v_head_50_);
if (v_isShared_54_ == 0)
{
lean_ctor_set(v___x_53_, 1, v_a_48_);
lean_ctor_set(v___x_53_, 0, v___x_55_);
v___x_57_ = v___x_53_;
goto v_reusejp_56_;
}
else
{
lean_object* v_reuseFailAlloc_59_; 
v_reuseFailAlloc_59_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_59_, 0, v___x_55_);
lean_ctor_set(v_reuseFailAlloc_59_, 1, v_a_48_);
v___x_57_ = v_reuseFailAlloc_59_;
goto v_reusejp_56_;
}
v_reusejp_56_:
{
v_a_47_ = v_tail_51_;
v_a_48_ = v___x_57_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_accounting_reverseEntries(lean_object* v_ps_61_){
_start:
{
lean_object* v___x_62_; lean_object* v___x_63_; 
v___x_62_ = lean_box(0);
v___x_63_ = lp_accounting_List_mapTR_loop___at___00reverseEntries_spec__0(v_ps_61_, v___x_62_);
return v___x_63_;
}
}
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOf_spec__0_spec__0(lean_object* v_a_64_, lean_object* v_as_65_, size_t v_i_66_, size_t v_stop_67_, lean_object* v_b_68_){
_start:
{
uint8_t v___x_69_; 
v___x_69_ = lean_usize_dec_eq(v_i_66_, v_stop_67_);
if (v___x_69_ == 0)
{
size_t v___x_70_; size_t v___x_71_; lean_object* v___x_72_; lean_object* v_account_73_; lean_object* v_amount_74_; uint8_t v___x_75_; 
v___x_70_ = ((size_t)1ULL);
v___x_71_ = lean_usize_sub(v_i_66_, v___x_70_);
v___x_72_ = lean_array_uget_borrowed(v_as_65_, v___x_71_);
v_account_73_ = lean_ctor_get(v___x_72_, 0);
v_amount_74_ = lean_ctor_get(v___x_72_, 1);
v___x_75_ = lean_nat_dec_eq(v_account_73_, v_a_64_);
if (v___x_75_ == 0)
{
v_i_66_ = v___x_71_;
goto _start;
}
else
{
lean_object* v___x_77_; 
v___x_77_ = lean_int_add(v_amount_74_, v_b_68_);
lean_dec(v_b_68_);
v_i_66_ = v___x_71_;
v_b_68_ = v___x_77_;
goto _start;
}
}
else
{
return v_b_68_;
}
}
}
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOf_spec__0_spec__0___boxed(lean_object* v_a_79_, lean_object* v_as_80_, lean_object* v_i_81_, lean_object* v_stop_82_, lean_object* v_b_83_){
_start:
{
size_t v_i_boxed_84_; size_t v_stop_boxed_85_; lean_object* v_res_86_; 
v_i_boxed_84_ = lean_unbox_usize(v_i_81_);
lean_dec(v_i_81_);
v_stop_boxed_85_ = lean_unbox_usize(v_stop_82_);
lean_dec(v_stop_82_);
v_res_86_ = lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOf_spec__0_spec__0(v_a_79_, v_as_80_, v_i_boxed_84_, v_stop_boxed_85_, v_b_83_);
lean_dec_ref(v_as_80_);
lean_dec(v_a_79_);
return v_res_86_;
}
}
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00balanceOf_spec__0(lean_object* v_a_87_, lean_object* v_init_88_, lean_object* v_l_89_){
_start:
{
lean_object* v___x_90_; lean_object* v___x_91_; lean_object* v___x_92_; uint8_t v___x_93_; 
v___x_90_ = lean_array_mk(v_l_89_);
v___x_91_ = lean_array_get_size(v___x_90_);
v___x_92_ = lean_unsigned_to_nat(0u);
v___x_93_ = lean_nat_dec_lt(v___x_92_, v___x_91_);
if (v___x_93_ == 0)
{
lean_dec_ref(v___x_90_);
return v_init_88_;
}
else
{
size_t v___x_94_; size_t v___x_95_; lean_object* v___x_96_; 
v___x_94_ = lean_usize_of_nat(v___x_91_);
v___x_95_ = ((size_t)0ULL);
v___x_96_ = lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOf_spec__0_spec__0(v_a_87_, v___x_90_, v___x_94_, v___x_95_, v_init_88_);
lean_dec_ref(v___x_90_);
return v___x_96_;
}
}
}
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00balanceOf_spec__0___boxed(lean_object* v_a_97_, lean_object* v_init_98_, lean_object* v_l_99_){
_start:
{
lean_object* v_res_100_; 
v_res_100_ = lp_accounting_List_foldrTR___at___00balanceOf_spec__0(v_a_97_, v_init_98_, v_l_99_);
lean_dec(v_a_97_);
return v_res_100_;
}
}
LEAN_EXPORT lean_object* lp_accounting_balanceOf(lean_object* v_led_101_, lean_object* v_a_102_){
_start:
{
lean_object* v___x_103_; lean_object* v___x_104_; 
v___x_103_ = lean_obj_once(&lp_accounting_List_sum___at___00postingSum_spec__0___closed__0, &lp_accounting_List_sum___at___00postingSum_spec__0___closed__0_once, _init_lp_accounting_List_sum___at___00postingSum_spec__0___closed__0);
v___x_104_ = lp_accounting_List_foldrTR___at___00balanceOf_spec__0(v_a_102_, v___x_103_, v_led_101_);
return v___x_104_;
}
}
LEAN_EXPORT lean_object* lp_accounting_balanceOf___boxed(lean_object* v_led_105_, lean_object* v_a_106_){
_start:
{
lean_object* v_res_107_; 
v_res_107_ = lp_accounting_balanceOf(v_led_105_, v_a_106_);
lean_dec(v_a_106_);
return v_res_107_;
}
}
static lean_object* _init_lp_accounting_roundHalfUp___closed__0(void){
_start:
{
lean_object* v___x_108_; lean_object* v___x_109_; 
v___x_108_ = lean_unsigned_to_nat(2u);
v___x_109_ = lean_nat_to_int(v___x_108_);
return v___x_109_;
}
}
LEAN_EXPORT lean_object* lp_accounting_roundHalfUp(lean_object* v_n_110_, lean_object* v_d_111_){
_start:
{
lean_object* v___x_112_; lean_object* v___x_113_; lean_object* v___x_114_; lean_object* v___x_115_; 
v___x_112_ = lean_obj_once(&lp_accounting_roundHalfUp___closed__0, &lp_accounting_roundHalfUp___closed__0_once, _init_lp_accounting_roundHalfUp___closed__0);
v___x_113_ = lean_int_ediv(v_d_111_, v___x_112_);
v___x_114_ = lean_int_add(v_n_110_, v___x_113_);
lean_dec(v___x_113_);
v___x_115_ = lean_int_ediv(v___x_114_, v_d_111_);
lean_dec(v___x_114_);
return v___x_115_;
}
}
LEAN_EXPORT lean_object* lp_accounting_roundHalfUp___boxed(lean_object* v_n_116_, lean_object* v_d_117_){
_start:
{
lean_object* v_res_118_; 
v_res_118_ = lp_accounting_roundHalfUp(v_n_116_, v_d_117_);
lean_dec(v_d_117_);
lean_dec(v_n_116_);
return v_res_118_;
}
}
static lean_object* _init_lp_accounting_splitVatInclusive___closed__0(void){
_start:
{
lean_object* v___x_119_; lean_object* v___x_120_; 
v___x_119_ = lean_unsigned_to_nat(1000u);
v___x_120_ = lean_nat_to_int(v___x_119_);
return v___x_120_;
}
}
LEAN_EXPORT lean_object* lp_accounting_splitVatInclusive(lean_object* v_gross_121_, lean_object* v_rate_122_){
_start:
{
lean_object* v___x_123_; lean_object* v___x_124_; lean_object* v___x_125_; lean_object* v___x_126_; lean_object* v___x_127_; lean_object* v___x_128_; lean_object* v___x_129_; lean_object* v___x_130_; lean_object* v___x_131_; 
v___x_123_ = lean_int_mul(v_gross_121_, v_rate_122_);
v___x_124_ = lean_obj_once(&lp_accounting_splitVatInclusive___closed__0, &lp_accounting_splitVatInclusive___closed__0_once, _init_lp_accounting_splitVatInclusive___closed__0);
v___x_125_ = lean_int_add(v___x_124_, v_rate_122_);
v___x_126_ = lean_obj_once(&lp_accounting_roundHalfUp___closed__0, &lp_accounting_roundHalfUp___closed__0_once, _init_lp_accounting_roundHalfUp___closed__0);
v___x_127_ = lean_int_ediv(v___x_125_, v___x_126_);
v___x_128_ = lean_int_add(v___x_123_, v___x_127_);
lean_dec(v___x_127_);
lean_dec(v___x_123_);
v___x_129_ = lean_int_ediv(v___x_128_, v___x_125_);
lean_dec(v___x_125_);
lean_dec(v___x_128_);
v___x_130_ = lean_int_sub(v_gross_121_, v___x_129_);
v___x_131_ = lean_alloc_ctor(0, 4, 0);
lean_ctor_set(v___x_131_, 0, v_gross_121_);
lean_ctor_set(v___x_131_, 1, v_rate_122_);
lean_ctor_set(v___x_131_, 2, v___x_129_);
lean_ctor_set(v___x_131_, 3, v___x_130_);
return v___x_131_;
}
}
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00amountsIn_spec__0_spec__0(lean_object* v_c_132_, lean_object* v_as_133_, size_t v_i_134_, size_t v_stop_135_, lean_object* v_b_136_){
_start:
{
uint8_t v___x_137_; 
v___x_137_ = lean_usize_dec_eq(v_i_134_, v_stop_135_);
if (v___x_137_ == 0)
{
size_t v___x_138_; size_t v___x_139_; lean_object* v___x_140_; lean_object* v_currency_141_; lean_object* v_amount_142_; uint8_t v___x_143_; 
v___x_138_ = ((size_t)1ULL);
v___x_139_ = lean_usize_sub(v_i_134_, v___x_138_);
v___x_140_ = lean_array_uget_borrowed(v_as_133_, v___x_139_);
v_currency_141_ = lean_ctor_get(v___x_140_, 1);
v_amount_142_ = lean_ctor_get(v___x_140_, 2);
v___x_143_ = lean_nat_dec_eq(v_currency_141_, v_c_132_);
if (v___x_143_ == 0)
{
v_i_134_ = v___x_139_;
goto _start;
}
else
{
lean_object* v___x_145_; 
lean_inc(v_amount_142_);
v___x_145_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_145_, 0, v_amount_142_);
lean_ctor_set(v___x_145_, 1, v_b_136_);
v_i_134_ = v___x_139_;
v_b_136_ = v___x_145_;
goto _start;
}
}
else
{
return v_b_136_;
}
}
}
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00amountsIn_spec__0_spec__0___boxed(lean_object* v_c_147_, lean_object* v_as_148_, lean_object* v_i_149_, lean_object* v_stop_150_, lean_object* v_b_151_){
_start:
{
size_t v_i_boxed_152_; size_t v_stop_boxed_153_; lean_object* v_res_154_; 
v_i_boxed_152_ = lean_unbox_usize(v_i_149_);
lean_dec(v_i_149_);
v_stop_boxed_153_ = lean_unbox_usize(v_stop_150_);
lean_dec(v_stop_150_);
v_res_154_ = lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00amountsIn_spec__0_spec__0(v_c_147_, v_as_148_, v_i_boxed_152_, v_stop_boxed_153_, v_b_151_);
lean_dec_ref(v_as_148_);
lean_dec(v_c_147_);
return v_res_154_;
}
}
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00amountsIn_spec__0(lean_object* v_c_155_, lean_object* v_init_156_, lean_object* v_l_157_){
_start:
{
lean_object* v___x_158_; lean_object* v___x_159_; lean_object* v___x_160_; uint8_t v___x_161_; 
v___x_158_ = lean_array_mk(v_l_157_);
v___x_159_ = lean_array_get_size(v___x_158_);
v___x_160_ = lean_unsigned_to_nat(0u);
v___x_161_ = lean_nat_dec_lt(v___x_160_, v___x_159_);
if (v___x_161_ == 0)
{
lean_dec_ref(v___x_158_);
return v_init_156_;
}
else
{
size_t v___x_162_; size_t v___x_163_; lean_object* v___x_164_; 
v___x_162_ = lean_usize_of_nat(v___x_159_);
v___x_163_ = ((size_t)0ULL);
v___x_164_ = lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00amountsIn_spec__0_spec__0(v_c_155_, v___x_158_, v___x_162_, v___x_163_, v_init_156_);
lean_dec_ref(v___x_158_);
return v___x_164_;
}
}
}
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00amountsIn_spec__0___boxed(lean_object* v_c_165_, lean_object* v_init_166_, lean_object* v_l_167_){
_start:
{
lean_object* v_res_168_; 
v_res_168_ = lp_accounting_List_foldrTR___at___00amountsIn_spec__0(v_c_165_, v_init_166_, v_l_167_);
lean_dec(v_c_165_);
return v_res_168_;
}
}
LEAN_EXPORT lean_object* lp_accounting_amountsIn(lean_object* v_c_169_, lean_object* v_ps_170_){
_start:
{
lean_object* v___x_171_; lean_object* v___x_172_; 
v___x_171_ = lean_box(0);
v___x_172_ = lp_accounting_List_foldrTR___at___00amountsIn_spec__0(v_c_169_, v___x_171_, v_ps_170_);
return v___x_172_;
}
}
LEAN_EXPORT lean_object* lp_accounting_amountsIn___boxed(lean_object* v_c_173_, lean_object* v_ps_174_){
_start:
{
lean_object* v_res_175_; 
v_res_175_ = lp_accounting_amountsIn(v_c_173_, v_ps_174_);
lean_dec(v_c_173_);
return v_res_175_;
}
}
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOfIn_spec__0_spec__0(lean_object* v_c_176_, lean_object* v_a_177_, lean_object* v_as_178_, size_t v_i_179_, size_t v_stop_180_, lean_object* v_b_181_){
_start:
{
uint8_t v___x_182_; 
v___x_182_ = lean_usize_dec_eq(v_i_179_, v_stop_180_);
if (v___x_182_ == 0)
{
size_t v___x_183_; size_t v___x_184_; lean_object* v___x_185_; lean_object* v_account_186_; lean_object* v_currency_187_; lean_object* v_amount_188_; uint8_t v___x_189_; 
v___x_183_ = ((size_t)1ULL);
v___x_184_ = lean_usize_sub(v_i_179_, v___x_183_);
v___x_185_ = lean_array_uget_borrowed(v_as_178_, v___x_184_);
v_account_186_ = lean_ctor_get(v___x_185_, 0);
v_currency_187_ = lean_ctor_get(v___x_185_, 1);
v_amount_188_ = lean_ctor_get(v___x_185_, 2);
v___x_189_ = lean_nat_dec_eq(v_currency_187_, v_c_176_);
if (v___x_189_ == 0)
{
v_i_179_ = v___x_184_;
goto _start;
}
else
{
uint8_t v___x_191_; 
v___x_191_ = lean_nat_dec_eq(v_account_186_, v_a_177_);
if (v___x_191_ == 0)
{
v_i_179_ = v___x_184_;
goto _start;
}
else
{
lean_object* v___x_193_; 
v___x_193_ = lean_int_add(v_amount_188_, v_b_181_);
lean_dec(v_b_181_);
v_i_179_ = v___x_184_;
v_b_181_ = v___x_193_;
goto _start;
}
}
}
else
{
return v_b_181_;
}
}
}
LEAN_EXPORT lean_object* lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOfIn_spec__0_spec__0___boxed(lean_object* v_c_195_, lean_object* v_a_196_, lean_object* v_as_197_, lean_object* v_i_198_, lean_object* v_stop_199_, lean_object* v_b_200_){
_start:
{
size_t v_i_boxed_201_; size_t v_stop_boxed_202_; lean_object* v_res_203_; 
v_i_boxed_201_ = lean_unbox_usize(v_i_198_);
lean_dec(v_i_198_);
v_stop_boxed_202_ = lean_unbox_usize(v_stop_199_);
lean_dec(v_stop_199_);
v_res_203_ = lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOfIn_spec__0_spec__0(v_c_195_, v_a_196_, v_as_197_, v_i_boxed_201_, v_stop_boxed_202_, v_b_200_);
lean_dec_ref(v_as_197_);
lean_dec(v_a_196_);
lean_dec(v_c_195_);
return v_res_203_;
}
}
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00balanceOfIn_spec__0(lean_object* v_c_204_, lean_object* v_a_205_, lean_object* v_init_206_, lean_object* v_l_207_){
_start:
{
lean_object* v___x_208_; lean_object* v___x_209_; lean_object* v___x_210_; uint8_t v___x_211_; 
v___x_208_ = lean_array_mk(v_l_207_);
v___x_209_ = lean_array_get_size(v___x_208_);
v___x_210_ = lean_unsigned_to_nat(0u);
v___x_211_ = lean_nat_dec_lt(v___x_210_, v___x_209_);
if (v___x_211_ == 0)
{
lean_dec_ref(v___x_208_);
return v_init_206_;
}
else
{
size_t v___x_212_; size_t v___x_213_; lean_object* v___x_214_; 
v___x_212_ = lean_usize_of_nat(v___x_209_);
v___x_213_ = ((size_t)0ULL);
v___x_214_ = lp_accounting___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00balanceOfIn_spec__0_spec__0(v_c_204_, v_a_205_, v___x_208_, v___x_212_, v___x_213_, v_init_206_);
lean_dec_ref(v___x_208_);
return v___x_214_;
}
}
}
LEAN_EXPORT lean_object* lp_accounting_List_foldrTR___at___00balanceOfIn_spec__0___boxed(lean_object* v_c_215_, lean_object* v_a_216_, lean_object* v_init_217_, lean_object* v_l_218_){
_start:
{
lean_object* v_res_219_; 
v_res_219_ = lp_accounting_List_foldrTR___at___00balanceOfIn_spec__0(v_c_215_, v_a_216_, v_init_217_, v_l_218_);
lean_dec(v_a_216_);
lean_dec(v_c_215_);
return v_res_219_;
}
}
LEAN_EXPORT lean_object* lp_accounting_balanceOfIn(lean_object* v_led_220_, lean_object* v_c_221_, lean_object* v_a_222_){
_start:
{
lean_object* v___x_223_; lean_object* v___x_224_; 
v___x_223_ = lean_obj_once(&lp_accounting_List_sum___at___00postingSum_spec__0___closed__0, &lp_accounting_List_sum___at___00postingSum_spec__0___closed__0_once, _init_lp_accounting_List_sum___at___00postingSum_spec__0___closed__0);
v___x_224_ = lp_accounting_List_foldrTR___at___00balanceOfIn_spec__0(v_c_221_, v_a_222_, v___x_223_, v_led_220_);
return v___x_224_;
}
}
LEAN_EXPORT lean_object* lp_accounting_balanceOfIn___boxed(lean_object* v_led_225_, lean_object* v_c_226_, lean_object* v_a_227_){
_start:
{
lean_object* v_res_228_; 
v_res_228_ = lp_accounting_balanceOfIn(v_led_225_, v_c_226_, v_a_227_);
lean_dec(v_a_227_);
lean_dec(v_c_226_);
return v_res_228_;
}
}
LEAN_EXPORT lean_object* lp_accounting_reverseCPosting(lean_object* v_p_229_){
_start:
{
lean_object* v_account_230_; lean_object* v_currency_231_; lean_object* v_amount_232_; lean_object* v___x_234_; uint8_t v_isShared_235_; uint8_t v_isSharedCheck_240_; 
v_account_230_ = lean_ctor_get(v_p_229_, 0);
v_currency_231_ = lean_ctor_get(v_p_229_, 1);
v_amount_232_ = lean_ctor_get(v_p_229_, 2);
v_isSharedCheck_240_ = !lean_is_exclusive(v_p_229_);
if (v_isSharedCheck_240_ == 0)
{
v___x_234_ = v_p_229_;
v_isShared_235_ = v_isSharedCheck_240_;
goto v_resetjp_233_;
}
else
{
lean_inc(v_amount_232_);
lean_inc(v_currency_231_);
lean_inc(v_account_230_);
lean_dec(v_p_229_);
v___x_234_ = lean_box(0);
v_isShared_235_ = v_isSharedCheck_240_;
goto v_resetjp_233_;
}
v_resetjp_233_:
{
lean_object* v___x_236_; lean_object* v___x_238_; 
v___x_236_ = lean_int_neg(v_amount_232_);
lean_dec(v_amount_232_);
if (v_isShared_235_ == 0)
{
lean_ctor_set(v___x_234_, 2, v___x_236_);
v___x_238_ = v___x_234_;
goto v_reusejp_237_;
}
else
{
lean_object* v_reuseFailAlloc_239_; 
v_reuseFailAlloc_239_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v_reuseFailAlloc_239_, 0, v_account_230_);
lean_ctor_set(v_reuseFailAlloc_239_, 1, v_currency_231_);
lean_ctor_set(v_reuseFailAlloc_239_, 2, v___x_236_);
v___x_238_ = v_reuseFailAlloc_239_;
goto v_reusejp_237_;
}
v_reusejp_237_:
{
return v___x_238_;
}
}
}
}
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00reverseCEntries_spec__0(lean_object* v_a_241_, lean_object* v_a_242_){
_start:
{
if (lean_obj_tag(v_a_241_) == 0)
{
lean_object* v___x_243_; 
v___x_243_ = l_List_reverse___redArg(v_a_242_);
return v___x_243_;
}
else
{
lean_object* v_head_244_; lean_object* v_tail_245_; lean_object* v___x_247_; uint8_t v_isShared_248_; uint8_t v_isSharedCheck_254_; 
v_head_244_ = lean_ctor_get(v_a_241_, 0);
v_tail_245_ = lean_ctor_get(v_a_241_, 1);
v_isSharedCheck_254_ = !lean_is_exclusive(v_a_241_);
if (v_isSharedCheck_254_ == 0)
{
v___x_247_ = v_a_241_;
v_isShared_248_ = v_isSharedCheck_254_;
goto v_resetjp_246_;
}
else
{
lean_inc(v_tail_245_);
lean_inc(v_head_244_);
lean_dec(v_a_241_);
v___x_247_ = lean_box(0);
v_isShared_248_ = v_isSharedCheck_254_;
goto v_resetjp_246_;
}
v_resetjp_246_:
{
lean_object* v___x_249_; lean_object* v___x_251_; 
v___x_249_ = lp_accounting_reverseCPosting(v_head_244_);
if (v_isShared_248_ == 0)
{
lean_ctor_set(v___x_247_, 1, v_a_242_);
lean_ctor_set(v___x_247_, 0, v___x_249_);
v___x_251_ = v___x_247_;
goto v_reusejp_250_;
}
else
{
lean_object* v_reuseFailAlloc_253_; 
v_reuseFailAlloc_253_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_253_, 0, v___x_249_);
lean_ctor_set(v_reuseFailAlloc_253_, 1, v_a_242_);
v___x_251_ = v_reuseFailAlloc_253_;
goto v_reusejp_250_;
}
v_reusejp_250_:
{
v_a_241_ = v_tail_245_;
v_a_242_ = v___x_251_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_accounting_reverseCEntries(lean_object* v_ps_255_){
_start:
{
lean_object* v___x_256_; lean_object* v___x_257_; 
v___x_256_ = lean_box(0);
v___x_257_ = lp_accounting_List_mapTR_loop___at___00reverseCEntries_spec__0(v_ps_255_, v___x_256_);
return v___x_257_;
}
}
LEAN_EXPORT lean_object* lp_accounting_conversionEntrySource(lean_object* v_fx_258_, lean_object* v_src_259_, lean_object* v_c_260_, lean_object* v_v_261_){
_start:
{
lean_object* v___x_262_; lean_object* v___x_263_; lean_object* v___x_264_; lean_object* v___x_265_; lean_object* v___x_266_; lean_object* v___x_267_; 
v___x_262_ = lean_int_neg(v_v_261_);
lean_inc(v_c_260_);
v___x_263_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_263_, 0, v_src_259_);
lean_ctor_set(v___x_263_, 1, v_c_260_);
lean_ctor_set(v___x_263_, 2, v___x_262_);
v___x_264_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_264_, 0, v_fx_258_);
lean_ctor_set(v___x_264_, 1, v_c_260_);
lean_ctor_set(v___x_264_, 2, v_v_261_);
v___x_265_ = lean_box(0);
v___x_266_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_266_, 0, v___x_264_);
lean_ctor_set(v___x_266_, 1, v___x_265_);
v___x_267_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_267_, 0, v___x_263_);
lean_ctor_set(v___x_267_, 1, v___x_266_);
return v___x_267_;
}
}
LEAN_EXPORT lean_object* lp_accounting_conversionEntryTarget(lean_object* v_fx_268_, lean_object* v_tgt_269_, lean_object* v_d_270_, lean_object* v_v_x27_271_){
_start:
{
lean_object* v___x_272_; lean_object* v___x_273_; lean_object* v___x_274_; lean_object* v___x_275_; lean_object* v___x_276_; lean_object* v___x_277_; 
v___x_272_ = lean_int_neg(v_v_x27_271_);
lean_inc(v_d_270_);
v___x_273_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_273_, 0, v_fx_268_);
lean_ctor_set(v___x_273_, 1, v_d_270_);
lean_ctor_set(v___x_273_, 2, v___x_272_);
v___x_274_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_274_, 0, v_tgt_269_);
lean_ctor_set(v___x_274_, 1, v_d_270_);
lean_ctor_set(v___x_274_, 2, v_v_x27_271_);
v___x_275_ = lean_box(0);
v___x_276_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_276_, 0, v___x_274_);
lean_ctor_set(v___x_276_, 1, v___x_275_);
v___x_277_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_277_, 0, v___x_273_);
lean_ctor_set(v___x_277_, 1, v___x_276_);
return v___x_277_;
}
}
LEAN_EXPORT lean_object* lp_accounting_restate(lean_object* v_n_278_, lean_object* v_d_279_){
_start:
{
lean_object* v___x_280_; lean_object* v___x_281_; lean_object* v___x_282_; lean_object* v___x_283_; lean_object* v___x_284_; lean_object* v___x_285_; lean_object* v___x_286_; lean_object* v___x_287_; 
v___x_280_ = l_Int_sign(v_n_278_);
v___x_281_ = lean_nat_abs(v_n_278_);
v___x_282_ = lean_nat_to_int(v___x_281_);
v___x_283_ = lean_obj_once(&lp_accounting_roundHalfUp___closed__0, &lp_accounting_roundHalfUp___closed__0_once, _init_lp_accounting_roundHalfUp___closed__0);
v___x_284_ = lean_int_ediv(v_d_279_, v___x_283_);
v___x_285_ = lean_int_add(v___x_282_, v___x_284_);
lean_dec(v___x_284_);
lean_dec(v___x_282_);
v___x_286_ = lean_int_ediv(v___x_285_, v_d_279_);
lean_dec(v___x_285_);
v___x_287_ = lean_int_mul(v___x_280_, v___x_286_);
lean_dec(v___x_286_);
lean_dec(v___x_280_);
return v___x_287_;
}
}
LEAN_EXPORT lean_object* lp_accounting_restate___boxed(lean_object* v_n_288_, lean_object* v_d_289_){
_start:
{
lean_object* v_res_290_; 
v_res_290_ = lp_accounting_restate(v_n_288_, v_d_289_);
lean_dec(v_d_289_);
lean_dec(v_n_288_);
return v_res_290_;
}
}
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00perLine_spec__0(lean_object* v_d_291_, lean_object* v_a_292_, lean_object* v_a_293_){
_start:
{
if (lean_obj_tag(v_a_292_) == 0)
{
lean_object* v___x_294_; 
v___x_294_ = l_List_reverse___redArg(v_a_293_);
return v___x_294_;
}
else
{
lean_object* v_head_295_; lean_object* v_tail_296_; lean_object* v___x_298_; uint8_t v_isShared_299_; uint8_t v_isSharedCheck_305_; 
v_head_295_ = lean_ctor_get(v_a_292_, 0);
v_tail_296_ = lean_ctor_get(v_a_292_, 1);
v_isSharedCheck_305_ = !lean_is_exclusive(v_a_292_);
if (v_isSharedCheck_305_ == 0)
{
v___x_298_ = v_a_292_;
v_isShared_299_ = v_isSharedCheck_305_;
goto v_resetjp_297_;
}
else
{
lean_inc(v_tail_296_);
lean_inc(v_head_295_);
lean_dec(v_a_292_);
v___x_298_ = lean_box(0);
v_isShared_299_ = v_isSharedCheck_305_;
goto v_resetjp_297_;
}
v_resetjp_297_:
{
lean_object* v___x_300_; lean_object* v___x_302_; 
v___x_300_ = lp_accounting_roundHalfUp(v_head_295_, v_d_291_);
lean_dec(v_head_295_);
if (v_isShared_299_ == 0)
{
lean_ctor_set(v___x_298_, 1, v_a_293_);
lean_ctor_set(v___x_298_, 0, v___x_300_);
v___x_302_ = v___x_298_;
goto v_reusejp_301_;
}
else
{
lean_object* v_reuseFailAlloc_304_; 
v_reuseFailAlloc_304_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_304_, 0, v___x_300_);
lean_ctor_set(v_reuseFailAlloc_304_, 1, v_a_293_);
v___x_302_ = v_reuseFailAlloc_304_;
goto v_reusejp_301_;
}
v_reusejp_301_:
{
v_a_292_ = v_tail_296_;
v_a_293_ = v___x_302_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_accounting_List_mapTR_loop___at___00perLine_spec__0___boxed(lean_object* v_d_306_, lean_object* v_a_307_, lean_object* v_a_308_){
_start:
{
lean_object* v_res_309_; 
v_res_309_ = lp_accounting_List_mapTR_loop___at___00perLine_spec__0(v_d_306_, v_a_307_, v_a_308_);
lean_dec(v_d_306_);
return v_res_309_;
}
}
LEAN_EXPORT lean_object* lp_accounting_perLine(lean_object* v_xs_310_, lean_object* v_d_311_){
_start:
{
lean_object* v___x_312_; lean_object* v___x_313_; lean_object* v___x_314_; 
v___x_312_ = lean_box(0);
v___x_313_ = lp_accounting_List_mapTR_loop___at___00perLine_spec__0(v_d_311_, v_xs_310_, v___x_312_);
v___x_314_ = lp_accounting_List_sum___at___00postingSum_spec__0(v___x_313_);
lean_dec(v___x_313_);
return v___x_314_;
}
}
LEAN_EXPORT lean_object* lp_accounting_perLine___boxed(lean_object* v_xs_315_, lean_object* v_d_316_){
_start:
{
lean_object* v_res_317_; 
v_res_317_ = lp_accounting_perLine(v_xs_315_, v_d_316_);
lean_dec(v_d_316_);
return v_res_317_;
}
}
LEAN_EXPORT lean_object* lp_accounting_perDoc(lean_object* v_xs_318_, lean_object* v_d_319_){
_start:
{
lean_object* v___x_320_; lean_object* v___x_321_; 
v___x_320_ = lp_accounting_List_sum___at___00postingSum_spec__0(v_xs_318_);
v___x_321_ = lp_accounting_roundHalfUp(v___x_320_, v_d_319_);
lean_dec(v___x_320_);
return v___x_321_;
}
}
LEAN_EXPORT lean_object* lp_accounting_perDoc___boxed(lean_object* v_xs_322_, lean_object* v_d_323_){
_start:
{
lean_object* v_res_324_; 
v_res_324_ = lp_accounting_perDoc(v_xs_322_, v_d_323_);
lean_dec(v_d_323_);
lean_dec(v_xs_322_);
return v_res_324_;
}
}
LEAN_EXPORT lean_object* lp_accounting_scaledErr(lean_object* v_d_325_, lean_object* v_x_326_){
_start:
{
lean_object* v___x_327_; lean_object* v___x_328_; lean_object* v___x_329_; lean_object* v___x_330_; lean_object* v___x_331_; 
v___x_327_ = lean_obj_once(&lp_accounting_roundHalfUp___closed__0, &lp_accounting_roundHalfUp___closed__0_once, _init_lp_accounting_roundHalfUp___closed__0);
v___x_328_ = lp_accounting_roundHalfUp(v_x_326_, v_d_325_);
v___x_329_ = lean_int_mul(v_d_325_, v___x_328_);
lean_dec(v___x_328_);
v___x_330_ = lean_int_sub(v___x_329_, v_x_326_);
lean_dec(v___x_329_);
v___x_331_ = lean_int_mul(v___x_327_, v___x_330_);
lean_dec(v___x_330_);
return v___x_331_;
}
}
LEAN_EXPORT lean_object* lp_accounting_scaledErr___boxed(lean_object* v_d_332_, lean_object* v_x_333_){
_start:
{
lean_object* v_res_334_; 
v_res_334_ = lp_accounting_scaledErr(v_d_332_, v_x_333_);
lean_dec(v_x_333_);
lean_dec(v_d_332_);
return v_res_334_;
}
}
LEAN_EXPORT lean_object* lp_accounting_applyGuarded(lean_object* v_lo_335_, lean_object* v_hi_336_, lean_object* v_bal_337_, lean_object* v_p_338_){
_start:
{
lean_object* v_amount_339_; lean_object* v___x_340_; uint8_t v___x_341_; 
v_amount_339_ = lean_ctor_get(v_p_338_, 1);
v___x_340_ = lean_int_add(v_bal_337_, v_amount_339_);
v___x_341_ = lean_int_dec_le(v_lo_335_, v___x_340_);
if (v___x_341_ == 0)
{
lean_dec(v___x_340_);
lean_inc(v_bal_337_);
return v_bal_337_;
}
else
{
uint8_t v___x_342_; 
v___x_342_ = lean_int_dec_le(v___x_340_, v_hi_336_);
if (v___x_342_ == 0)
{
lean_dec(v___x_340_);
lean_inc(v_bal_337_);
return v_bal_337_;
}
else
{
return v___x_340_;
}
}
}
}
LEAN_EXPORT lean_object* lp_accounting_applyGuarded___boxed(lean_object* v_lo_343_, lean_object* v_hi_344_, lean_object* v_bal_345_, lean_object* v_p_346_){
_start:
{
lean_object* v_res_347_; 
v_res_347_ = lp_accounting_applyGuarded(v_lo_343_, v_hi_344_, v_bal_345_, v_p_346_);
lean_dec_ref(v_p_346_);
lean_dec(v_bal_345_);
lean_dec(v_hi_344_);
lean_dec(v_lo_343_);
return v_res_347_;
}
}
LEAN_EXPORT lean_object* lp_accounting_List_foldl___at___00runGuarded_spec__0(lean_object* v_lo_348_, lean_object* v_hi_349_, lean_object* v_x_350_, lean_object* v_x_351_){
_start:
{
if (lean_obj_tag(v_x_351_) == 0)
{
return v_x_350_;
}
else
{
lean_object* v_head_352_; lean_object* v_tail_353_; lean_object* v___x_354_; 
v_head_352_ = lean_ctor_get(v_x_351_, 0);
v_tail_353_ = lean_ctor_get(v_x_351_, 1);
v___x_354_ = lp_accounting_applyGuarded(v_lo_348_, v_hi_349_, v_x_350_, v_head_352_);
lean_dec(v_x_350_);
v_x_350_ = v___x_354_;
v_x_351_ = v_tail_353_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_accounting_List_foldl___at___00runGuarded_spec__0___boxed(lean_object* v_lo_356_, lean_object* v_hi_357_, lean_object* v_x_358_, lean_object* v_x_359_){
_start:
{
lean_object* v_res_360_; 
v_res_360_ = lp_accounting_List_foldl___at___00runGuarded_spec__0(v_lo_356_, v_hi_357_, v_x_358_, v_x_359_);
lean_dec(v_x_359_);
lean_dec(v_hi_357_);
lean_dec(v_lo_356_);
return v_res_360_;
}
}
LEAN_EXPORT lean_object* lp_accounting_runGuarded(lean_object* v_lo_361_, lean_object* v_hi_362_, lean_object* v_start_363_, lean_object* v_ps_364_){
_start:
{
lean_object* v___x_365_; 
v___x_365_ = lp_accounting_List_foldl___at___00runGuarded_spec__0(v_lo_361_, v_hi_362_, v_start_363_, v_ps_364_);
return v___x_365_;
}
}
LEAN_EXPORT lean_object* lp_accounting_runGuarded___boxed(lean_object* v_lo_366_, lean_object* v_hi_367_, lean_object* v_start_368_, lean_object* v_ps_369_){
_start:
{
lean_object* v_res_370_; 
v_res_370_ = lp_accounting_runGuarded(v_lo_366_, v_hi_367_, v_start_368_, v_ps_369_);
lean_dec(v_ps_369_);
lean_dec(v_hi_367_);
lean_dec(v_lo_366_);
return v_res_370_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
void lean_initialize_runtime_module();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_accounting_Accounting(uint8_t builtin) {
lean_object * res;
if (_G_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_initialized = true;
lean_initialize_runtime_module();
res = initialize_Init(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_Init(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
