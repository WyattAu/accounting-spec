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
lean_object* l_List_foldr___at___00Lean_Omega_IntList_sum_spec__0(lean_object*, lean_object*);
lean_object* lean_int_neg(lean_object*);
lean_object* lean_int_mul(lean_object*, lean_object*);
lean_object* lean_int_add(lean_object*, lean_object*);
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
LEAN_EXPORT lean_object* lp_accounting_reversePosting(lean_object* v_p_12_){
_start:
{
lean_object* v___x_13_; 
v___x_13_ = lean_int_neg(v_p_12_);
return v___x_13_;
}
}
LEAN_EXPORT lean_object* lp_accounting_reversePosting___boxed(lean_object* v_p_14_){
_start:
{
lean_object* v_res_15_; 
v_res_15_ = lp_accounting_reversePosting(v_p_14_);
lean_dec(v_p_14_);
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
static lean_object* _init_lp_accounting_roundHalfUp___closed__0(void){
_start:
{
lean_object* v___x_19_; lean_object* v___x_20_; 
v___x_19_ = lean_unsigned_to_nat(2u);
v___x_20_ = lean_nat_to_int(v___x_19_);
return v___x_20_;
}
}
LEAN_EXPORT lean_object* lp_accounting_roundHalfUp(lean_object* v_n_21_, lean_object* v_d_22_){
_start:
{
lean_object* v___x_23_; lean_object* v___x_24_; lean_object* v___x_25_; lean_object* v___x_26_; 
v___x_23_ = lean_obj_once(&lp_accounting_roundHalfUp___closed__0, &lp_accounting_roundHalfUp___closed__0_once, _init_lp_accounting_roundHalfUp___closed__0);
v___x_24_ = lean_int_ediv(v_d_22_, v___x_23_);
v___x_25_ = lean_int_add(v_n_21_, v___x_24_);
lean_dec(v___x_24_);
v___x_26_ = lean_int_ediv(v___x_25_, v_d_22_);
lean_dec(v___x_25_);
return v___x_26_;
}
}
LEAN_EXPORT lean_object* lp_accounting_roundHalfUp___boxed(lean_object* v_n_27_, lean_object* v_d_28_){
_start:
{
lean_object* v_res_29_; 
v_res_29_ = lp_accounting_roundHalfUp(v_n_27_, v_d_28_);
lean_dec(v_d_28_);
lean_dec(v_n_27_);
return v_res_29_;
}
}
static lean_object* _init_lp_accounting_splitVatInclusive___closed__0(void){
_start:
{
lean_object* v___x_30_; lean_object* v___x_31_; 
v___x_30_ = lean_unsigned_to_nat(1000u);
v___x_31_ = lean_nat_to_int(v___x_30_);
return v___x_31_;
}
}
LEAN_EXPORT lean_object* lp_accounting_splitVatInclusive(lean_object* v_gross_32_, lean_object* v_rate_33_){
_start:
{
lean_object* v___x_34_; lean_object* v___x_35_; lean_object* v___x_36_; lean_object* v___x_37_; lean_object* v___x_38_; lean_object* v___x_39_; lean_object* v___x_40_; lean_object* v___x_41_; lean_object* v___x_42_; 
v___x_34_ = lean_int_mul(v_gross_32_, v_rate_33_);
v___x_35_ = lean_obj_once(&lp_accounting_splitVatInclusive___closed__0, &lp_accounting_splitVatInclusive___closed__0_once, _init_lp_accounting_splitVatInclusive___closed__0);
v___x_36_ = lean_int_add(v___x_35_, v_rate_33_);
v___x_37_ = lean_obj_once(&lp_accounting_roundHalfUp___closed__0, &lp_accounting_roundHalfUp___closed__0_once, _init_lp_accounting_roundHalfUp___closed__0);
v___x_38_ = lean_int_ediv(v___x_36_, v___x_37_);
v___x_39_ = lean_int_add(v___x_34_, v___x_38_);
lean_dec(v___x_38_);
lean_dec(v___x_34_);
v___x_40_ = lean_int_ediv(v___x_39_, v___x_36_);
lean_dec(v___x_36_);
lean_dec(v___x_39_);
v___x_41_ = lean_int_sub(v_gross_32_, v___x_40_);
v___x_42_ = lean_alloc_ctor(0, 4, 0);
lean_ctor_set(v___x_42_, 0, v_gross_32_);
lean_ctor_set(v___x_42_, 1, v_rate_33_);
lean_ctor_set(v___x_42_, 2, v___x_40_);
lean_ctor_set(v___x_42_, 3, v___x_41_);
return v___x_42_;
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
