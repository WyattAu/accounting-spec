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
lean_object* lean_array_mk(lean_object*);
lean_object* lean_array_get_size(lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
size_t lean_usize_of_nat(lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
size_t lean_usize_sub(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* lean_int_add(lean_object*, lean_object*);
lean_object* lean_int_mul(lean_object*, lean_object*);
lean_object* lean_int_ediv(lean_object*, lean_object*);
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
