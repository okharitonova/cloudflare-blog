#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

#define __unused __attribute__((unused))

char __license[] SEC("license") = "GPL";

struct {
	__uint(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uint(max_entries, 1);
	__uint(key_size, sizeof(__u32));
	__uint(value_size, sizeof(__u32));
} jmp_table SEC(".maps");

SEC("tc")
int target_prog(struct __sk_buff *skb __unused)
{
	return 0xcafe;
}

SEC("tc")
int entry_prog(struct __sk_buff *skb)
{
	bpf_tail_call(skb, &jmp_table, 0);
	return 0xf00d;
}
